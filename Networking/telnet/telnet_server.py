import asyncio
import subprocess

def run_command(com: str) -> None:
	try:
		pro = subprocess.run(com.split(), capture_output=True, text=True)
		if pro.stdout:
			return f"out----------------\n{pro.stdout}"
		elif pro.stderr:
			return f"err----------------\n {pro.stderr}"
		else:
			return f"[executed]"
	except Exception as ex:
		print("exception occured", ex)
		return f"   [subprocess broke]" 

async def handle_client(reader, writer):
    print(f"Connected to {writer.get_extra_info('peername')}")

    while True:
        data = await reader.read(100000)
        message = data.decode().strip()
        if not message:
            break
        print(f"Received message: {message}")
        res = run_command(message)
        writer.write(res.encode())
    print("Closing connection")
    writer.close()

async def start_server():
    server = await asyncio.start_server(handle_client, "127.0.0.1", 2000)
    print("Server started")
    await server.serve_forever()

asyncio.run(start_server())