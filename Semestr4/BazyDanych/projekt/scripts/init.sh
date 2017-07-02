POSTGRES_DB="Conference"
POSTGRES_USER="confCreator"
POSTGRES_PASS="confCreatorPassword"

sudo -u postgres psql -c "CREATE USER $POSTGRES_USER WITH SUPERUSER PASSWORD '$POSTGRES_PASS';"
sudo -u postgres psql -c "CREATE DATABASE $POSTGRES_DB OWNER $POSTGRES_USER ENCODING 'Unicode';"

sudo apt-get update
sudo apt-get install python-pip
sudo pip install psycopg2 passlib