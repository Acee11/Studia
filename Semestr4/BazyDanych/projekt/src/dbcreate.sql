CREATE TYPE TALK_STATUS AS ENUM ('waiting', 'accepted', 'rejected');
CREATE TYPE USER_STATUS AS ENUM ('organizer', 'normal user');

CREATE TABLE ConfUser (
	login 			TEXT 			NOT NULL PRIMARY KEY,
	passwdHash 		TEXT 			NOT NULL,
	status 			USER_STATUS 	NOT NULL
);

CREATE TABLE Event (
	id				TEXT 		NOT NULL PRIMARY KEY,
	startTimestamp 	TIMESTAMP 	NOT NULL,
	endTimestamp 	TIMESTAMP 	NOT NULL
);

CREATE TABLE Talk (
	id 				TEXT 				NOT NULL PRIMARY KEY,
	title 			TEXT 				NOT NULL,
	startTimestamp 	TIMESTAMP 			NOT NULL,
	roomId 			TEXT 	 			,
	eventId			TEXT 	 			REFERENCES Event(id),
	userId 			TEXT 				NOT NULL REFERENCES ConfUser(login),
	status 			TALK_STATUS			NOT NULL,
	creationDate	timestamp 			NOT NULL DEFAULT NOW()
);


CREATE TABLE Rating (
	userId 			TEXT 	 	NOT NULL REFERENCES ConfUser(login),
	talkId			TEXT 		NOT NULL REFERENCES Talk(id),
	ratingVal		INTEGER		NOT NULL,
	UNIQUE(userId, talkId),

	CHECK(ratingVal BETWEEN 0 AND 10)	
);

CREATE TABLE FriendRequest (
	userId1			TEXT 	 	NOT NULL REFERENCES ConfUser(login),
	userId2			TEXT 	 	NOT NULL REFERENCES ConfUser(login),
	UNIQUE(userId1, userId2),

	CHECK (userId1 != userId2)
);

CREATE TABLE Friends (
	userId1			TEXT 	 	REFERENCES ConfUser(login),
	userId2			TEXT 	 	REFERENCES ConfUser(login),
	UNIQUE(userId1, userId2),

	CHECK (userId1 != userId2)
);


CREATE TABLE Presence (
	userId 			TEXT 	 	NOT NULL REFERENCES ConfUser(login),
	talkId			TEXT 	 	NOT NULL REFERENCES Talk(id),
	UNIQUE(userId, talkId)
);

CREATE TABLE RegisteredOnEvent (
	userId 			TEXT 	 	NOT NULL REFERENCES ConfUser(login),
	eventId			TEXT 	 	NOT NULL REFERENCES Event(id),
	UNIQUE(userId, eventId)
);


CREATE OR REPLACE FUNCTION managePresence() RETURNS TRIGGER AS
$X$
BEGIN
	IF ((SELECT status FROM Talk WHERE id = NEW.talkId) != 'accepted') THEN
		RAISE integrity_constraint_violation;
	END IF;
	RETURN NEW;
END
$X$
LANGUAGE plpgsql;

CREATE TRIGGER onInsertToPresence 
BEFORE INSERT ON Presence
FOR EACH ROW EXECUTE PROCEDURE managePresence();

CREATE OR REPLACE FUNCTION manageFriendRequest() RETURNS TRIGGER AS
$X$
BEGIN
	IF ((NEW.userId2, NEW.userId1) IN (SELECT * FROM FriendRequest)) THEN
		INSERT INTO Friends VALUES(NEW.userId1, NEW.userId2);
		DELETE FROM FriendRequest fr WHERE 
			fr.userid1 = NEW.userid2 AND fr.userid2 = NEW.userid1;
		RETURN NULL;
	END IF;
	RETURN NEW;
END
$X$
LANGUAGE plpgsql;

CREATE TRIGGER onInsertToFriendRequest 
BEFORE INSERT ON FriendRequest
FOR EACH ROW EXECUTE PROCEDURE manageFriendRequest();

CREATE OR REPLACE FUNCTION manageNewRating() RETURNS TRIGGER AS
$X$
BEGIN
	IF((SELECT status FROM Talk WHERE id = NEW.talkId) != 'accepted') THEN
		RAISE integrity_constraint_violation;
	END IF;
	IF((NEW.userId, NEW.talkId) IN (SELECT userid,talkid FROM Rating)) THEN
		UPDATE Rating R SET ratingVal = NEW.ratingVal 
			WHERE R.userid = NEW.userid AND R.talkid = NEW.talkid;
		RETURN NULL;
	END IF;
	RETURN NEW;
END
$X$
LANGUAGE plpgsql;

CREATE TRIGGER onInsertToRating 
BEFORE INSERT ON Rating
FOR EACH ROW EXECUTE PROCEDURE manageNewRating();


CREATE OR REPLACE FUNCTION registerTalk(
	speakerLoginArg text,
	talkArg text,
	titleArg text,
	startTimestampArg timestamp,
	roomArg text,
	initialEvaluationArg int,
	eventNameArg text
	)
RETURNS VOID AS
$X$
BEGIN
	IF(talkArg in (SELECT id from talk)) THEN
		UPDATE talk SET
		userid = speakerLoginArg,
		title = titleArg,
		startTimestamp = startTimestampArg,
		roomid = roomArg,
		eventid = eventNameArg,
		status = 'accepted'
		WHERE id = talkArg;
	ELSE
		INSERT INTO talk(id, title, startTimestamp, roomid, 
						eventid, userid, status, creationDate)
		VALUES (talkArg, titleArg, startTimestampArg, roomArg, 
				eventNameArg, speakerLoginArg, 'accepted', DEFAULT);
	END IF;
	
	INSERT INTO Rating(userid, talkid, ratingVal)
	VALUES (speakerLoginArg, talkArg, initialEvaluationArg);

	RETURN;
END
$X$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION getUserPlan(
	loginArg text, 
	lim int
) 
RETURNS TABLE(loginRes text, talk text, startTime timestamp, title text, room text) AS
$X$
BEGIN
	IF(lim = 0) THEN lim := NULL; END IF;

	RETURN QUERY
	WITH userEvents(evId) AS (SELECT eventId FROM RegisteredOnEvent WHERE userid = loginArg)
	SELECT loginArg, t.id, t.startTimestamp, t.title, t.roomid FROM userEvents uEv 
	JOIN Event Ev ON(uEv.evId = Ev.id)
	JOIN Talk t ON (Ev.id = t.eventid)
	WHERE t.status = 'accepted'
	ORDER BY t.startTimestamp
	LIMIT lim;
END
$X$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION getDayPlan(
	startTimeArg timestamp
)
RETURNS TABLE(talk text, startTime timestamp, title text, room text) AS
$X$
BEGIN
	RETURN QUERY
	SELECT t.id, t.startTimestamp, t.title, t.roomid FROM Talk t
	WHERE EXTRACT(DAY FROM t.startTimestamp) = EXTRACT(DAY FROM startTimeArg)
	AND t.status = 'accepted'
	ORDER BY t.startTimestamp;
END
$X$
LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION getBestTalks(
	startTime timestamp, 
	endTime timestamp,
	lim int,
	allArg int
)  
RETURNS TABLE(talk text, startTimeRes timestamp, title text, room text) AS
$X$
BEGIN
	IF(lim = 0) THEN lim := NULL; END IF;
	IF(allArg = 1) THEN
		RETURN QUERY
		SELECT t.id, t.startTimestamp, t.title, t.roomid
		FROM Talk t
		JOIN Rating rt ON (rt.talkid = t.id)
		WHERE t.startTimestamp BETWEEN startTime AND endTime
		AND t.status = 'accepted'
		GROUP BY t.id, t.title, t.startTimestamp, t.roomid
		ORDER BY avg(rt.ratingVal) DESC
		LIMIT lim;
	ELSE
		RETURN QUERY
		SELECT t.id, t.startTimestamp, t.title, t.roomid
		FROM Talk t
		JOIN Rating rt ON (rt.talkid = t.id)
		JOIN ConfUser us ON (us.login = rt.userid)
		JOIN Presence pr ON (pr.userid = us.login AND pr.talkid = t.id)
		WHERE t.startTimestamp BETWEEN startTime AND endTime
		AND t.status = 'accepted'
		GROUP BY t.id, t.title, t.startTimestamp, t.roomid
		ORDER BY avg(rt.ratingVal) DESC
		LIMIT lim;
	END IF;
END
$X$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION getMostPopularTalks(
	startTime timestamp, 
	endTime timestamp,
	lim int
)  
RETURNS TABLE(talk text, startTimeRes timestamp, title text, room text) AS
$X$
BEGIN
	IF(lim = 0) THEN lim := NULL; END IF;

	RETURN QUERY
	SELECT t.id, t.startTimestamp, t.title, t.roomid
	FROM Talk t
	JOIN Presence pr ON (pr.talkid = t.id)
	WHERE t.startTimestamp BETWEEN startTime AND endTime
	AND t.status = 'accepted'
	GROUP BY t.id, t.title, t.startTimestamp, t.roomid
	ORDER BY count(*) DESC
	LIMIT lim;
END
$X$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION getAttendedTalks(
	loginArg text
)  
RETURNS TABLE(talk text, startTime timestamp, title text, room text) AS
$X$
BEGIN
	RETURN QUERY
	WITH attendedTalks(tid) AS (SELECT talkid FROM Presence WHERE userid = loginArg)
	SELECT t.id, t.startTimestamp, t.title, t.roomid
	FROM attendedTalks at
	JOIN Talk t ON (at.tid = t.id);
END
$X$
LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION getAbandonedTalks(
	lim int
)  
RETURNS TABLE(talk text, startTime timestamp, title text, room text, cnt bigint) AS
$X$
BEGIN
	IF(lim = 0) THEN lim := NULL; END IF;

	RETURN QUERY
	WITH tmpcnt(id, cnt) AS 
	(
		SELECT t.id, count(pr.userid) 
		FROM Talk t
		JOIN Event ev ON (t.eventid = ev.id)
		JOIN RegisteredOnEvent roe ON (ev.id = roe.eventid)
		LEFT JOIN Presence pr ON (t.id = pr.talkid AND roe.userid = pr.userid)
		WHERE t.eventid IS NOT NULL
		GROUP BY t.id, t.title, t.startTimestamp, t.roomid, ev.id
	)
	SELECT t.id, t.startTimestamp, t.title, t.roomid, count(roe.userid) - tmpcnt.cnt
	FROM Talk t
	JOIN Event ev ON (t.eventid = ev.id)
	LEFT JOIN RegisteredOnEvent roe ON (ev.id = roe.eventid)
	JOIN tmpcnt ON (tmpcnt.id = t.id)
	WHERE t.eventid IS NOT NULL
	GROUP BY t.id, t.title, t.startTimestamp, t.roomid, ev.id, tmpcnt.cnt
	ORDER BY count(roe.userid) - tmpcnt.cnt DESC
	LIMIT lim;
END
$X$
LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION getRecentlyAddedTalks(
	lim int
)  
RETURNS TABLE(talk text, speakerLogin text, startTime timestamp, title text, room text) AS
$X$
BEGIN
	IF(lim = 0) THEN lim := NULL; END IF;

	RETURN QUERY
	SELECT t.id, us.login, t.startTimestamp, t.title, t.roomid
	FROM Talk t
	JOIN ConfUser us ON(t.userid = us.login)
	ORDER BY t.creationDate DESC
	LIMIT lim;
END
$X$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION getRejectedTalks(
	loginArg text
)  
RETURNS TABLE(talk text, speakerLogin text, startTimestamp timestamp, title text) AS
$X$
DECLARE
	userStatusVar USER_STATUS;
BEGIN
	SELECT status INTO userStatusVar FROM confUser WHERE login = loginArg;
	IF(userStatusVar = 'organizer') THEN
		RETURN QUERY
		SELECT t.id, us.login, t.startTimestamp, t.title 
		FROM Talk t
		JOIN ConfUser us ON (us.login = t.userid)
		WHERE t.status = 'rejected';
	ELSE
		RETURN QUERY
		SELECT t.id, loginArg, t.startTimestamp, t.title 
		FROM Talk t
		WHERE t.status = 'rejected' AND t.userid = loginArg;
	END IF;

END
$X$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION getProposals()  
RETURNS TABLE(talk text, speakerLogin text, startTimestamp timestamp, title text) AS
$X$
BEGIN
	RETURN QUERY
	SELECT t.id, us.login, t.startTimestamp, t.title 
	FROM Talk t
	JOIN ConfUser us ON (t.userid = us.login)
	WHERE t.status = 'waiting';

END
$X$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION getFriendsTalks(
	loginArg text,
	startTime timestamp, 
	endTime timestamp,
	lim int
)  
RETURNS TABLE(talk text, speakerLogin text, startTimestamp timestamp, title text, room text) AS
$X$
BEGIN
	IF(lim = 0) THEN lim := NULL; END IF;

	RETURN QUERY
	WITH fr(frid1, frid2) AS 
	(SELECT * FROM Friends f WHERE f.userid1 = loginArg OR f.userid2 = loginArg)
	SELECT t.id, us.login, t.startTimestamp, t.title, t.roomid
	FROM Talk t
	JOIN ConfUser us ON (t.userid = us.login)
	JOIN fr ON (t.userid = fr.frid1 OR t.userid = fr.frid2)
	WHERE t.userid != loginArg
	AND t.startTimestamp BETWEEN startTime AND endTime
	AND t.status = 'accepted'
	ORDER BY t.startTimestamp
	LIMIT lim;

END
$X$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION getFriendsOnEvent(
	loginArg text,
	eventName text
)
RETURNS TABLE(loginRes text , eventNameRes text, friendLogin text) AS
$X$
BEGIN
	RETURN QUERY
	WITH fr(frid1, frid2) AS 
	(SELECT f.userid1, f.userid2 FROM Friends f WHERE f.userid1 = loginArg OR f.userid2 = loginArg)
	SELECT loginArg, eventName, us.login
	FROM Event ev
	JOIN RegisteredOnEvent roe ON(ev.id = roe.eventid)
	JOIN ConfUser us ON (roe.userid = us.login)
	JOIN fr ON (roe.userid = fr.frid1 OR roe.userid = fr.frid2)
	WHERE ev.id = eventName
	AND us.login != loginArg;

END
$X$
LANGUAGE plpgsql;