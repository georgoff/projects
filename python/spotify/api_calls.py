#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon May 18 21:28:49 2020

@author: georgoff
"""

import requests



### USER TASTE ###
# Endpoints for retrieving information about the user’s listening habits.

def GetTopSomething(typeToGet, userToken, limit = '20', offset = '0', timeRange = 'medium_term'):
    # Get the current user’s top artists or tracks based on calculated affinity.
    
    # Requires user token from authorization service and "user-top-read" scope
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
        'limit':str(limit),
        'offset':str(offset),
        'time_range':timeRange
        }
    
    r = requests.get(address, headers=headers, params=payload)
    
    return r.json()



### TRACKS ###
# Endpoints for retrieving information about one or more tracks from the Spotify catalog.

def GetTrack(userToken, trackId):
    # Get Spotify catalog information for a single track identified by its unique Spotify ID.
    
    # Requires user token from authorization service (no scope)
    # trackId: The Spotify ID for the desired track
    # There is an optional "market" query parameter (not implemented here)
    # that can be used for track relinking
    
    address = f'https://api.spotify.com/v1/tracks/{trackId}'
    headers = {'Authorization':f'Bearer {userToken}'}
    
    r = requests.get(address, headers=headers)
    
    return r.json()

def GetSeveralTracks(userToken, trackIds):
    # Get Spotify catalog information for multiple tracks based on their Spotify IDs.
    
    # Requires user token from authorization service (no scope)
    # trackIds: A list of Spotify IDs for the desired tracks (max of 50)
    # There is an optional "market" query parameter (not implemented here)
    # that can be used for track relinking
    
    parameterString = '?ids='
    
    for track in trackIds:
        parameterString += f'{track},'
    
    address = 'https://api.spotify.com/v1/tracks/' + parameterString.strip(',')
    headers = {'Authorization':f'Bearer {userToken}'}
    
    r = requests.get(address, headers=headers)
    
    return r.json()

def GetTrackAudioFeatures(userToken, trackId):
    # Get audio feature information for a single track identified by its unique Spotify ID.
    
    # Requires user token from authorization service (no scope)
    # trackId: The Spotify ID for the desired track
    
    address = f'https://api.spotify.com/v1/audio-features/{trackId}'
    headers = {'Authorization':f'Bearer {userToken}'}
    
    r = requests.get(address, headers=headers)
    
    return r.json()

def GetMultipleTrackAudioFeatures(userToken, trackIds):
    # Get audio features for multiple tracks based on their Spotify IDs.
    
    # Requires user token from authorization service (no scope)
    # trackIds: A list of Spotify IDs for the desired tracks (max 100)
    
    parameterString = '?ids='
    
    for track in trackIds:
        parameterString += f'{track},'
    
    address = 'https://api.spotify.com/v1/audio-features/' + parameterString.strip(',')
    headers = {'Authorization':f'Bearer {userToken}'}
    
    r = requests.get(address, headers=headers)
    
    return r.json()

def GetTrackAudioAnalysis(userToken, trackId):
    # Get a detailed audio analysis for a single track identified by its unique Spotify ID.
    
    # Requires user token from the authorization service (no scope)
    # trackId: The Spotify ID for the desired track
    
    address = f'https://api.spotify.com/v1/audio-analysis/{trackId}'
    headers = {'Authorization':f'Bearer {userToken}'}
    
    r = requests.get(address, headers=headers)
    
    return r.json()



### BROWSE ###
# Endpoints for getting playlists and new album releases featured on Spotify’s Browse tab.

def GetCategory(userToken, categoryId):
    # Get a single category used to tag items in Spotify (on, for example, the Spotify player’s “Browse” tab).
    
    # Requires user token from authorization service (no scope)
    # categoryId: The Spotify Category ID for the desired category
    # There are optional "country" and "locale" query parameters
    # (not implemented here) that control country availability and
    # results language
    
    address = f'https://api.spotify.com/v1/browse/categories/{categoryId}'
    headers = {'Authorization':f'Bearer {userToken}'}
    
    r = requests.get(address, headers=headers)
    
    return r.json()

def GetCategoryPlaylists(userToken, categoryId, limit = 20, offset = 0):
    # Get a list of Spotify playlists tagged with a particular category.
    
    # Requires user token from authorization service (no scope)
    # categoryId: The Spotify Category ID for the desired category
    # limit: (optional) The number of entries to return. Min = 1, Max = 50
    # offset: (optional) The index of the first entity to return
    # There is an optional "country" query parameter (not implemented here)
    # that controls the country result
    
    address = f'https://api.spotify.com/v1/browse/categories/{categoryId}/playlists'
    headers = {'Authorization':f'Bearer {userToken}'}
    payload = {
        'limit':str(limit),
        'offset':str(offset)
        }
    
    r = requests.get(address, headers=headers, params=payload)
    
    return r.json()

def GetListOfCategories(userToken, limit = 20, offset = 0):
    # Get a list of categories used to tag items in Spotify (on, for example, the Spotify player’s “Browse” tab).
    
    # Requires user token from authorization service (no scope)
    # limit: (optional) The number of entries to return. Min = 1, Max = 50
    # offset: (optional) The index of the first entity to return
    # There are optional "country" and "locale" query parameters
    # (not implemented here) that control country availability and
    # results language
    
    address = f'https://api.spotify.com/v1/browse/categories'
    headers = {'Authorization':f'Bearer {userToken}'}
    payload = {
        'limit':str(limit),
        'offset':str(offset)
        }
    
    r = requests.get(address, headers=headers, params=payload)
    
    return r.json()