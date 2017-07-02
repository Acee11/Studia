CREATE OR REPLACE FUNCTION myfunc(int) 
RETURNS grupa.termin%TYPE AS
$X$
	SELECT termin FROM grupa WHERE kod_grupy = $1;
$X$
LANGUAGE SQL; 

