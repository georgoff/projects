#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat May 16 22:41:00 2020

@author: georgoff
"""

import requests

token = 'PUT_TOKEN_HERE'

def GetTopSomething(typeToGet, userToken, limit = '20', offset = '0', timeRange = 'medium_term'):
    # Requires user token and "user-top-read" scope
    # typeToGet: "artists" or "tracks"
    # limit: (optional) The number of entries to return. Min = 1, Max = 50
    # offset: (optional) The index of the first entity to return
    # time_range: (optional) Over what time frame the affinites are computed
        # "long_term": calculated from several years of data
        # "medium_term": approximately last 6 months
        # "short_term": approximately last 4 weeks
    
    address = f'https://api.spotify.com/v1/me/top/{typeToGet}'
    headers = {'Authorization':f'Bearer {userToken}'}
    payload = {
        'limit':limit,
        'offset':offset,
        'time_range':timeRange
        }
    
    r = requests.get(address, headers=headers, params=payload)
    
    return r.json()

def GetToken(authCode, redirectUri, clientId, clientSecret, refresh = False):
    # authCode: The authorization code returned from the initial request to the
    #           /authorize endpoint OR the refresh token if refresh == True
    # grantType: Must contain 'authorization_code'
    # redirectUri: Used for validation. Must contain the exact value of redirect_uri
    #              supplied when requesting the authorization code
    
    address = 'https://accounts.spotify.com/api/token'
    
    if refresh:
        payload = {
            'grant_type':'refresh_token',
            'client_id':clientId,
            'client_secret':clientSecret,
            'refresh_token':authCode
            }
    else:
        payload = {
            'grant_type':'authorization_code',
            'code':authCode,
            'redirect_uri':redirectUri,
            'client_id':clientId,
            'client_secret':clientSecret
            }
    
    r = requests.post(address, data=payload)
    
    return r.json()

myTopSongs = GetTopSomething('tracks', token, limit = '35', timeRange = 'short_term')

for i in myTopSongs['items']:
    print(i['name'])