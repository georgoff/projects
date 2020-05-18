#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun May 17 20:48:31 2020

@author: georgoff
"""

import requests

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
    
    rJson = r.json()
    
    return rJson['access_token'], rJson['expires_in'], rJson['refresh_token'], rJson['scope']

