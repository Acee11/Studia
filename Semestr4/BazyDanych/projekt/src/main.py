import json
import dbHandler
import IO

def main():
	inputReader = IO.stdinInputReader()
	handler = dbHandler.db_handler()

	while(True):
		rpc = inputReader.next()
		if inputReader.endOfStream:
			break
		print(handler(rpc))
	handler.disconnect()


if __name__ == '__main__':
	main()
