#!/usr/bin/env python

"""
A simple echo server
From http://ilab.cs.byu.edu/python/socket/echoserver.html
"""

import socket

host = ''
port = 9999
backlog = 5
size = 1024
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((host,port))
s.listen(backlog)
while 1:
  client, address = s.accept()
  data = client.recv(size)
  if data:
    print(data)
    client.send(data)
  client.close()
