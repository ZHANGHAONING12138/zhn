# -*- coding: utf-8 -*-
import sys
from threading import Lock
from math import radians, cos, sin, asin, sqrt, atan, acos, tan
from flask import Flask, request, jsonify

app = Flask(__name__)
mutex = Lock()

radius_a = 6378.140
radius_b = 6356.755

# the distance threshold which is used to judge whether player can capture the flag, or player can steal the flag...
# default value is 100 meters and can be configured by api: '/configure'
dist_threshold = 0.1

# the player quantity in a team, default value is 5 and can be configured by api '/configure'
player_cnt = 1

# the cp quantity for a team, default value is 4 and can be configured by api '/configure'
cp_cnt = 2

cp_locations = [
    {
        'id': 'cp1',
        'lat': '34.020203',
        'lng': '-118.288816',
        'mac': 'B8:27:EB:DB:1D:A4',
        'team': '1'
    },
    {
        'id': 'cp2',
        'lat': '34.019923',
        'lng': '-118.288690',
        'mac': 'B8:27:EB:FB:D5:7B',
        'team': '2'
    }
]

players = []
player_to_team = {}
player_to_op_team = {}
to_be_assigned_index = 0

player_locations = {}

# which flag the player is carrying now
flag_carrying_status = {}

# the flag status for both team
flag_status = {}

# the score status for both team
score_status = {}

# the flag locations after being captured by enemy
flag_location_list = {}


def init_data_structures():
    global to_be_assigned_index, players, player_to_team, player_to_op_team, \
        to_be_assigned_index, player_locations, flag_carrying_status, flag_status, score_status, flag_location_list

    to_be_assigned_index = 0
    players = []
    player_to_team = {}
    player_to_op_team = {}
    to_be_assigned_index = 0

    player_locations = {}
    flag_carrying_status = {}
    flag_status = {}
    score_status = {}
    flag_location_list = {}

    for index in range(player_cnt):
        player = 'p' + str(index + 1)
        flag_carrying_status[player] = []
        player_to_team[player] = '1'
        player_to_op_team[player] = '2'
        players.append({'team': '1', 'index': index + 1})
    for index in range(player_cnt):
        player = 'p' + str(player_cnt + index + 1)
        flag_carrying_status[player] = []
        player_to_team[player] = '2'
        player_to_op_team[player] = '1'
        players.append({'team': '2', 'index': player_cnt + index + 1})

    flag_status['1'] = {'Latitude': '', 'Longitude': '', 'Base': True, 'Team': '1'}
    flag_status['2'] = {'Latitude': '', 'Longitude': '', 'Base': True, 'Team': '2'}
    flag_location_list['1'] = []
    flag_location_list['2'] = []
    score_status['1'] = {'Team': '1', 'Score': '0'}
    score_status['2'] = {'Team': '2', 'Score': '0'}


def cal_distance(lat0, lng0, lat1, lng1):
    if lat1 - lat0 < 0.0000001 and lng1 - lng0 < 0.0000001:
        return 0

    flatten = (radius_a - radius_b) / radius_a
    rad_lat_0 = radians(lat0)
    rad_lng_0 = radians(lng0)
    rad_lat_1 = radians(lat1)
    rad_lng_1 = radians(lng1)
    p_a = atan(radius_b / radius_a * tan(rad_lat_0))
    p_b = atan(radius_b / radius_a * tan(rad_lat_1))
    xx = acos(sin(p_a) * sin(p_b) + cos(p_a) * cos(p_b) * cos(rad_lng_0 - rad_lng_1))
    c1 = (sin(xx) - xx) * (sin(p_a) + sin(p_b)) ** 2 / cos(xx / 2) ** 2
    c2 = (sin(xx) + xx) * (sin(p_a) - sin(p_b)) ** 2 / sin(xx / 2) ** 2
    dr = flatten / 8 * (c1 - c2)
    distance = radius_a * (xx + dr)
    return distance


# judge whether a player captures the flag from cp
def judge_capture_from_cp(op_team, lat, lng):
    for _, cp in enumerate(cp_locations):
        if cp['team'] == op_team:
            cp_lat = float(cp['lat'])
            cp_lng = float(cp['lng'])

            if cal_distance(cp_lat, cp_lng, lat, lng) <= dist_threshold:
                flag_status[op_team]['Base'] = False
                flag_status[op_team]['Latitude'] = str(lat)
                flag_status[op_team]['Longitude'] = str(lng)
                flag_location_list[op_team].append({'lat': lat, 'lng': lng})
                return True

    return False


# judge whether a player put back his own team's flag to cp
def judge_putback_flag_to_cp(team, lat, lng):
    for _, cp in enumerate(cp_locations):
        if cp['team'] == team:
            cp_lat = float(cp['lat'])
            cp_lng = float(cp['lng'])

            dist = cal_distance(cp_lat, cp_lng, lat, lng)
            if dist <= dist_threshold:
                flag_status[team]['Latitude'] = ''
                flag_status[team]['Longitude'] = ''
                flag_status[team]['Base'] = True
                flag_location_list[team] = []
                return True

    return False


# judge whether the team scores
def judge_score(team, op_team, lat, lng):
    for _, cp in enumerate(cp_locations):
        if cp['team'] == team:
            cp_lat = float(cp['lat'])
            cp_lng = float(cp['lng'])

            #if cal_distance(cp_lat, cp_lng, lat, lng) <= dist_threshold and flag_status[team]['Base'] == True:
            if flag_status[team]['Base'] == True:

                tmp_score = score_status[team]['Score']
                score_status[team]['Score'] = str(int(tmp_score) + 1)
                flag_status[op_team]['Latitude'] = ''
                flag_status[op_team]['Longitude'] = ''
                flag_status[op_team]['Base'] = True
                flag_location_list[op_team] = []
                return True

    return False


def check_dist(p1, p2):
    loc1 = player_locations[p1]
    loc2 = player_locations[p2]

    dist = cal_distance(loc1['lat'], loc1['lng'], loc2['lat'], loc2['lng'])
    if dist < dist_threshold:
        return True
    else:
        return False


@app.route('/reset')
def reset():
    init_data_structures()
    return jsonify({
        'status': 'ok',
        'msg': 'reset succeeded'
    })


@app.route('/hello')
def hello():
    global to_be_assigned_index
    if to_be_assigned_index >= player_cnt * 2:
        return jsonify({
            'status': 'error',
            'msg': 'all players have been assigned'
        })

    mutex.acquire()
    player = players[to_be_assigned_index]
    to_be_assigned_index += 1
    result_msg = {
        'Player': 'p' + str(player['index']),
        'Team': player['team'],
        'CapturePoints': cp_locations
    }
    mutex.release()
    return jsonify(result_msg)


@app.route('/configure')
def configure():
    global player_cnt, cp_cnt, dist_threshold

    configured = []
    tmp = request.args.get('player_cnt')
    if tmp:
        player_cnt = int(tmp)
        configured.append('player_cnt')

    tmp = request.args.get('cp_cnt')
    if tmp:
        cp_cnt = int(tmp)
        configured.append('cp_cnt')

    tmp = request.args.get('dist_threshold')
    if tmp:
        dist_threshold = float(tmp)
        configured.append('dist_threshold')

    init_data_structures()
    return jsonify({'status': 'OK', 'msg': 'configured items: [%s]' % ','.join(configured)})


@app.route('/flag_locations')
def flag_locations():
    team = request.args.get('team')
    return jsonify(flag_location_list[team])


@app.route('/report_location')
def report_location():
    mutex.acquire()

    player = request.args.get('player')
    lat = request.args.get('latitude')
    lng = request.args.get('longitude')
    connected = request.args.get('connected')

    if not player or not lat or not lng:
        return jsonify({
            'status': 'error',
            'msg': 'params: player, latitude and longitude are all required'
        })

    lat = float(lat)
    lng = float(lng)
    player_locations[player] = {'lat': lat, 'lng': lng}

    if connected and connected != 'cp':
        # if check_dist(player, connected):
        flag_carrying_status[player].extend(flag_carrying_status[connected])
        flag_carrying_status[connected] = []
    else:
        carrying_status = flag_carrying_status[player]
        team = player_to_team[player]
        op_team = player_to_op_team[player]

        if team in carrying_status and connected == 'cp':
            if judge_putback_flag_to_cp(team, lat, lng):
                carrying_status.remove(team)

        if op_team in carrying_status:
            if connected == 'cp' and judge_score(team, op_team, lat, lng):
                carrying_status.remove(op_team)
            else:
                flag_status[op_team]['Latitude'] = str(lat)
                flag_status[op_team]['Longitude'] = str(lng)
                flag_location_list[op_team].append({'lat': lat, 'lng': lng})
        else:
            if connected == 'cp':
                if judge_capture_from_cp(op_team, lat, lng):
                    carrying_status.append(op_team)

    mutex.release()
    return jsonify({
        'CarryingFlag': len(flag_carrying_status[player]) > 0,
        'FlagLocations': [
            flag_status['1'],
            flag_status['2']
        ],
        'Score': [
            score_status['1'],
            score_status['2']
        ]
    })

@app.route('/')
def helloworld():
    return '<h1>Home Page of EE579 Team 1<h1>'

if __name__ == '__main__':

    port = 5000
    print('starting the main thread on port: ', port)

    init_data_structures()
    app.run(host='0.0.0.0', port=int(port))
