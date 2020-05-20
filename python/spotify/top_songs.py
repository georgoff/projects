#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat May 16 22:41:00 2020

@author: georgoff
"""

from api_calls import *
from authorization import GetToken
from user_secrets import clientId, clientSecret, refreshToken

token, expiresIn, refreshToken, scope = GetToken(refreshToken, clientId, clientSecret, refresh = True)

# myTopSongs = GetTopSomething('tracks', token, limit = '35', timeRange = 'short_term')

# for i in myTopSongs['items']:
#     print(i['name'])

sampleCategories = GetListOfCategories(token)