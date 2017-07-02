import os
import sys
import psycopg2
from passlib.hash import pbkdf2_sha256

HOST_NAME = 'localhost'
SECRET = 'd8578edf8458ce06fbc5bb76a58c5ca4'
SCRIPT_PATH = 'dbcreate.sql'


class DBError(Exception):
	pass

class db_handler(object):
	def __init__(self):
		self.conn = None

	def create(self):
		if self.conn is None:
			return
		try:
			self.cur.execute(open(SCRIPT_PATH, 'r').read())
			self.conn.commit()
		except OSError:
			print('SQL script not found')
			os._exit(1)

	def isEmpty(self):
		self.cur.execute(
			"""SELECT * FROM information_schema.tables
			WHERE table_type = 'BASE TABLE' AND table_schema = 'public'"""
		)
		row = self.cur.fetchone()

		self.conn.rollback()
		return row is None

	def disconnect(self):
		if self.conn is not None:
			self.conn.close()

	def opendb(self, args):
		try:
			self.conn = psycopg2.connect( 
		    	host=HOST_NAME, 
		    	user=args['login'], 
		    	password=args['password'], 
		    	dbname=args['baza'] 
		    )
			self.cur = self.conn.cursor()
			if self.isEmpty():
				self.create()
			return []
		except:
			raise DBError("Error while connecting to databse")

	def organizer(self, args):
		if(args['secret'] != SECRET):
			raise DBError("Authentication Failed!")
	
		passwdHash = pbkdf2_sha256.hash(args['newpassword'])
		self.cur.execute(
			"INSERT INTO confUser(login, passwdHash, status)"
			"VALUES (%s, %s, 'organizer')",
			(args['newlogin'], passwdHash)
		)
		self.conn.commit()
		return []

	def event(self, args):
		self.cur.execute(
			"INSERT INTO event(id, startTimestamp, endTimestamp)"
			"VALUES (%s, %s, %s)",
			(args['eventname'], args['start_timestamp'], args['end_timestamp'],)
		)
		self.conn.commit()
		return []

	def user(self, args):
		passwdHash = pbkdf2_sha256.hash(args['newpassword'])
		self.cur.execute(
			"INSERT INTO confUser(login, passwdHash, status)"
			"VALUES (%s, %s, %s)",
			(args['newlogin'], passwdHash, 'normal user',)
		)
		self.conn.commit()
		return []

	def talk(self, args):
		if args['eventname'] == '':
			args['eventname'] = None
		self.cur.execute(
			"SELECT registerTalk(%s, %s, %s, %s, %s, %s, %s)",
			(args['speakerlogin'], args['talk'], args['title'],
			args['start_timestamp'], args['room'], 
			args['initial_evaluation'], args['eventname'],)
		)
		self.conn.commit()
		return []


	def register_user_for_event(self, args):
		self.cur.execute(
			"INSERT INTO registeredOnEvent(userid, eventid)"
			"VALUES (%s, %s)",
			(args['login'], args['eventname'])
		)
		self.conn.commit()
		return []


	def attendance(self, args):
		self.cur.execute(
			"INSERT INTO presence(userid, talkid)"
			"VALUES (%s, %s)",
			(args['login'], args['talk'])
		)
		self.conn.commit()
		return []

	def evaluation(self, args):
		self.cur.execute(
			"INSERT INTO rating(userid, talkid, ratingval)"
			"VALUES (%s, %s, %s)",
			(args['login'], args['talk'], args['rating'])
		)
		self.conn.commit()
		return []

	def reject(self, args):
		self.cur.execute(
			"UPDATE talk "
			"SET status = 'rejected' "
			"WHERE id = %s",
			(args['talk'],)
		)
		self.conn.commit()
		return []

	def proposal(self, args):
		self.cur.execute(
			"INSERT INTO "
			"talk(id, title, startTimestamp, roomid, eventid, userid, status, creationDate) "
			"VALUES (%s, %s, %s, NULL, NULL, %s, 'waiting', DEFAULT)",
			(args['talk'], args['title'], args['start_timestamp'], args['login'],)
		)
		self.conn.commit()
		return []

	def friends(self, args):
		self.cur.execute(
			"INSERT INTO "
			"FriendRequest(userid1, userid2) "
			"VALUES (%s, %s)",
			(args['login1'], args['login2'],)
		)
		self.conn.commit()
		return []

	def user_plan(self, args):
		self.cur.execute(
			"SELECT * FROM getUserPlan(%s, %s)",
			(args['login'], args['limit'])
		)
		rows = self.cur.fetchall()

		res = []
		for row in rows:
			res.append({
				'login' : row[0],
				'talk' : row[1],
				'start_timestamp' : str(row[2]),
				'title' : row[3],
				'room' : row[4]
				}
			)
		return res

	def day_plan(self, args):
		self.cur.execute(
			"SELECT * FROM getDayPlan(%s)",
			(args['timestamp'],)
		)
		rows = self.cur.fetchall()

		res = []
		for row in rows:
			res.append({
				'talk' : row[0],
				'start_timestamp' : str(row[1]),
				'title' : row[2],
				'room' : row[3]
				}
			)
		return res

	def best_talks(self, args):
		self.cur.execute(
			"SELECT * FROM getBestTalks(%s, %s, %s, %s)",
			(args['start_timestamp'], args['end_timestamp'], args['limit'], args['all'],)
		)
		rows = self.cur.fetchall()

		res = []
		for row in rows:
			res.append({
				'talk' : row[0],
				'start_timestamp' : str(row[1]),
				'title' : row[2],
				'room' : row[3]
				}
			)
		return res

	def most_popular_talks(self, args):
		self.cur.execute(
			"SELECT * FROM getMostPopularTalks(%s, %s, %s)",
			(args['start_timestamp'], args['end_timestamp'], args['limit'],)
		)
		rows = self.cur.fetchall()

		res = []
		for row in rows:
			res.append({
				'talk' : row[0],
				'start_timestamp' : str(row[1]),
				'title' : row[2],
				'room' : row[3]
				}
			)
		return res

	def attended_talks(self, args):
		self.cur.execute(
			"SELECT * FROM getAttendedTalks(%s)",
			(args['login'],)
		)
		rows = self.cur.fetchall()

		res = []
		for row in rows:
			res.append({
				'talk' : row[0],
				'start_timestamp' : str(row[1]),
				'title' : row[2],
				'room' : row[3]
				}
			)
		return res

	def abandoned_talks(self, args):
		self.cur.execute(
			"SELECT * FROM getAbandonedTalks(%s)",
			(args['limit'],)
		)
		rows = self.cur.fetchall()

		res = []
		for row in rows:
			res.append({
				'talk' : row[0],
				'start_timestamp' : str(row[1]),
				'title' : row[2],
				'room' : row[3],
				'number' : row[4]
				}
			)
		return res

	def recently_added_talks(self, args):
		self.cur.execute(
			"SELECT * FROM getRecentlyAddedTalks(%s)",
			(args['limit'],)
		)
		rows = self.cur.fetchall()

		res = []
		for row in rows:
			res.append({
				'talk' : row[0],
				'speaker_login' : row[1],
				'start_timestamp' : str(row[2]),
				'title' : row[3],
				'room' : row[4]
				}
			)
		return res

	def rejected_talks(self, args):
		self.cur.execute(
			"SELECT * FROM getRejectedTalks(%s)",
			(args['login'],)
		)
		rows = self.cur.fetchall()

		res = []
		for row in rows:
			res.append({
				'talk' : row[0],
				'speaker_login' : row[1],
				'start_timestamp' : str(row[2]),
				'title' : row[3]
				}
			)
		return res

	def proposals(self, args):
		self.cur.execute(
			"SELECT * FROM getProposals()"
		)
		rows = self.cur.fetchall()

		res = []
		for row in rows:
			res.append({
				'talk' : row[0],
				'speaker_login' : row[1],
				'start_timestamp' : str(row[2]),
				'title' : row[3]
				}
			)
		return res

	def friends_talks(self, args):
		self.cur.execute(
			"SELECT * FROM getFriendsTalks(%s, %s, %s, %s)",
			(args['login'], args['start_timestamp'], 
			args['end_timestamp'], args['limit'],)
		)
		rows = self.cur.fetchall()

		res = []
		for row in rows:
			res.append({
				'talk' : row[0],
				'speaker_login' : row[1],
				'start_timestamp' : str(row[2]),
				'title' : row[3],
				'room' : row[4]
				}
			)
		return res

	def friends_events(self, args):
		self.cur.execute(
			"SELECT * FROM getFriendsOnEvent(%s, %s)",
			(args['login'], args['eventname'],)
		)
		rows = self.cur.fetchall()

		res = []
		for row in rows:
			res.append({
				'login' : row[0],
				'eventname' : row[1],
				'friendlogin' : row[2]
				}
			)
		return res

	def allowed(self, login, passwd, privileges):
		if privileges == 'none':
			return True
		else:
			if privileges == 'organizer':
				self.cur.execute(
					"SELECT status FROM confUser WHERE login = %s", (login,)
					)
				rows = self.cur.fetchall()
				if(rows[0][0] != 'organizer'):
					return False

			self.cur.execute(
				"SELECT passwdHash FROM confUser WHERE login = %s", (login,)
				)
			try:
				passwdHash = self.cur.fetchall()[0][0]
			except IndexError:
				return False
			return pbkdf2_sha256.verify(passwd, passwdHash)

	functions = {
		'open' : {
			'privileges' : 'none',
			'func' : opendb
		},

		'organizer' : {
			'privileges' : 'none',
			'func' : organizer
		},

		'event' : {
			'privileges' : 'organizer',
			'func' : event
		},

		'user' : {
			'privileges' : 'organizer',
			'func' : user
		},

		'talk' : {
			'privileges' : 'organizer',
			'func' : talk
		},

		'register_user_for_event' : {
			'privileges' : 'user',
			'func' : register_user_for_event
		},

		'attendance' : {
			'privileges' : 'user',
			'func' : attendance
		},

		'evaluation' : {
			'privileges' : 'user',
			'func' : evaluation
		},

		'reject' : {
			'privileges' : 'organizer',
			'func' : reject
		},

		'proposal' : {
			'privileges' : 'user',
			'func' : proposal
		},

		'friends' : {
			'privileges' : 'user',
			'func' : friends
		},

		'user_plan' : {
			'privileges' : 'none',
			'func' : user_plan,
		},

		'day_plan' : {
			'privileges' : 'none',
			'func' : day_plan
		},

		'best_talks' : {
			'privileges' : 'none',
			'func' : best_talks
		},

		'most_popular_talks' : {
			'privileges' : 'none',
			'func' : most_popular_talks
		},

		'attended_talks' : {
			'privileges' : 'user',
			'func' : attended_talks
		},

		'abandoned_talks' : {
			'privileges' : 'organizer',
			'func' : abandoned_talks
		},

		'recently_added_talks' : {
			'privileges' : 'none',
			'func' : recently_added_talks
		},

		'rejected_talks' : {
			'privileges' : 'user',
			'func' : rejected_talks
		},

		'proposals' : {
			'privileges' : 'organizer',
			'func' : proposals
		},

		'friends_talks' : {
			'privileges' : 'user',
			'func' : friends_talks
		},

		'friends_events' : {
			'privileges' : 'user',
			'func' : friends_events
		},
	}

	def __call__(self, json_rpc):
		try:
			fname_list = list(json_rpc)
			if len(fname_list) != 1:
				raise NotImplementedError
			fname = fname_list[0]
			if fname not in db_handler.functions:
				raise NotImplementedError
			fdata = db_handler.functions[fname]
			args = json_rpc[fname]
			if 'login1' in args:
				args['login'] = args['login1']
			if fdata['privileges'] != 'none':
				if not self.allowed(
					args['login'], 
					args['password'], 
					fdata['privileges']):

					return {'status' : 'ERROR', 'description' : "Authentication failed!"}

			ret_data = fdata['func'](self, args)
			return { 'status' : 'OK', 'data' : ret_data}
		except KeyError:
			return {'status' : 'ERROR', 'description' : 'Wrong rpc format'}
		except NotImplementedError:
			return {'status' : 'NOT IMPLEMENTED'}
		except psycopg2.IntegrityError:
			self.conn.rollback()
			return {'status' : 'ERROR', 'description' : 'Probably inserting redundant data'}
		except psycopg2.DataError:
			self.conn.rollback()
			return {'status' : 'ERROR', 'description' :'Probably inserting data in wrong format'}
		except DBError as e:
			return {'status' : 'ERROR', 'description' : e.args[0]}
