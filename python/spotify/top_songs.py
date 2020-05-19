#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat May 16 22:41:00 2020

@author: georgoff
"""

from api_calls import GetTopSomething

token = 'PUT_TOKEN_HERE'

myTopSongs = GetTopSomething('tracks', token, limit = '35', timeRange = 'short_term')

for i in myTopSongs['items']:
    print(i['name'])