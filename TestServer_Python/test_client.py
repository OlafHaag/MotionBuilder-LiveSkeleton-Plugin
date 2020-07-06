"""
Python dummy client to read data from server.
It's purpose is only to make sure the interface is working as expected.
"""
import sys
import time

sys.path.append('gen-py')

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

from LiveSkeletonTransfer import LiveSkeletonService

# Create a client that is used to send estimated data to the server.
transport = TSocket.TSocket('127.0.0.1', 9090)
transport = TTransport.TFramedTransport(transport)
protocol = TBinaryProtocol.TBinaryProtocol(transport)
client = LiveSkeletonService.Client(protocol)
transport.open()

try:
    print("Pulling data from server.")
    while True:
        data = client.getSkeletonData()
        print(data)
        time.sleep(0.5)

except KeyboardInterrupt:
    print("Quitting from keyboard interrupt.")
    transport.close()
