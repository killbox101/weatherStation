from flask import Flask, request, jsonify
from flask.ext.sqlalchemy import SQLAlchemy
from flask.ext.cors import cross_origin
#import datetime
from datetime import datetime, date, timedelta
app = Flask(__name__)
#cors = CORS(app)
db = SQLAlchemy(app)


app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://wsUpdate:password@localhost/wsTemp'

class Sighting(db.Model):
  __tablename__ = 'sightings'
  id = db.Column(db.Integer, primary_key = True)
  sighted_at = db.Column(db.Integer)
  reported_at = db.Column(db.Integer)
  location = db.Column(db.String(100))
  shape = db.Column(db.String(10))
  duration = db.Column(db.String(10))
  description = db.Column(db.Text)
  lat = db.Column(db.Float(6))
  lng = db.Column(db.Float(6))


class Weather2(db.Model):
    __tablename__ = 'wsT'
    id = db.Column(db.Integer, primary_key = True)
    temp = db.Column(db.String(10))
    humidity = db.Column(db.String(10))
    windSpeed = db.Column(db.String(10))
    windDirection = db.Column(db.String(10))


class Weather4(db.Model):
    __tablename__ = 'wsT4'
    id = db.Column(db.Integer, primary_key = True)
    DateRecorded = db.Column(db.TIMESTAMP)
    DHTCelcius = db.Column(db.Float(3))
    DHTFarenheight = db.Column(db.Float(3))
    DHTHeatIndex = db.Column(db.Float(3))
    DHTHumidity = db.Column(db.Float(3))
    BaroCelcius = db.Column(db.Float(3))
    BaroPressure = db.Column(db.Float(3))



class Weather(db.Model):
    __tablename__ = 'wsT3'
    id = db.Column(db.Integer, primary_key = True)
    DateRecorded = db.Column(db.TIMESTAMP)
    DHTCelcius = db.column(db.String(10))
    DHTFarenheight= db.column(db.String(10))
    DHTHeatIndex = db.column(db.String(10))
    DHTHumidity = db.column(db.String(10))
    BaroCelcius = db.column(db.String(10))
    BaroPressure = db.column(db.String(10))
    WindSpeedAvg = db.column(db.String(10))
    WindSpeedMin = db.column(db.String(10))
    WindSpeedMax = db.column(db.String(10))
    WindDirection = db.column(db.String(10))




@app.route('/sightings/', methods=['GET'])
def sightings():

    if request.method == 'GET':

        lim = request.args.get('limit', 10)
        off = request.args.get('offset', 0)

        radius = request.args.get('radius', 10)
        location = request.args.get('location', ',')
        lat, lng = location.split(',')

        if lat and lng and radius:
          query = "SELECT id,  location, ( 3959 * acos( cos( radians( %(latitude)s ) ) * cos( radians( lat ) ) * cos( radians( lng ) - radians( %(longitude)s ) ) + sin( radians( %(latitude)s ) ) * sin( radians( lat ) ) ) ) AS distance FROM sightings HAVING distance < %(radius)s ORDER BY distance LIMIT %(limit)s" % {"latitude": lat, "longitude": lng, "radius": radius, "limit": lim}

          results = Sighting.query.from_statement(query).all()

        else:
          results = Sighting.query.limit(lim).offset(off).all()

        json_results = []
        for result in results:
          d = {'sighted_at': result.sighted_at,
               'reported_at': result.reported_at,
               'location': result.location,
               'shape': result.shape,
               'duration': result.duration,
               'description': result.description,
               'lat': result.lat,
               'lng': result.lng}
          json_results.append(d)

        return jsonify(items=json_results)


@app.route('/sightings/<int:sighting_id>', methods=['GET'])
def sighting(sighting_id):
  if request.method == 'GET':
    result = Sighting.query.filter_by(id=sighting_id).first()

    json_result = {'sighted_at': result.sighted_at,
                   'reported_at': result.reported_at,
                   'location': result.location,
                   'shape': result.shape,
                   'duration': result.duration,
                   'description': result.description,
                   'lat': result.lat,
                   'lng': result.lng}

    return jsonify(items=json_result)    


@app.route('/weather/', methods = ['GET', 'POST'])
def weather():

    if request.method == 'GET':
        #results = Weather.query.limit(2).offset(0).all()
        results = Weather.query.all()

        json_results = []

        for result in results:
            d={
                'ID': result.id,
                #'teme_stamp': result.DateRecorded,
                'temp_Celcuis': result.DHTCelcius,
                'temp_Farenheight': result.DHTFarenheight,
                'temp_HeatIndex': result.DHTHeatIndex,
                'temp_Humidity': result.DHTHumidity,
                'baro_Celcius': result.BaroCelcius,
                #'baro_Pressure': result.BaroPressure,
                #'windSpeed_Avg': result.WindSpeedAvg,
                #'windSpeed_Min': result.WindSpeedMin,
                #'windSpeed_Max': result.WindSpeedMax,
                'windDirection':result.WindDirection}
            json_results.append(d)

        return jsonify(items=json_results)

    else: # must be a post

        DHT_c = request.args.get('DHTc')
        DHT_f = request.args.get('DHTf')
        DHT_hi = request.args.get('DHThi')
        DHT_h = request.args.get('DHTh')
        BARO_c = request.args.get('BAROc')
        BARO_p = request.args.get('BAROp')
        WS_avg = request.args.get('WSavg')
        WS_min = request.args.get('WSmin')
        WS_max = request.args.get('WSmax')
        WS_dir = request.args.get('WSdir')


        #result = Weather.query.add(temp=temp,humidity=humidity,windSpeed=windSpeed,windDirection=windDirection)
        #query = "INSERT INTO wsT (temp,humidity,windSpeed,windDirection) values (\'%s\',\'%s\',\'%s\',\'%s\')" %(t,h,wS,wD)
        query = "INSERT INTO wsT3 (DHTCelcius,DHTFarenheight,DHTHeatIndex,DHTHumidity,BaroCelcius,BaroPressure,WindSpeedAvg,WindSpeedMin,WindSpeedMax,WindDirection) values (\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')" %(DHT_c,DHT_f,DHT_hi,DHT_h,BARO_c,BARO_p,WS_avg,WS_min,WS_max,WS_dir)
        Weather.query.from_statement(query).all()
        Weather.flush()


@app.route('/weather2/', methods = ['GET', 'POST'])
def weather2():
    if request.method == 'GET':
        #results = Weather2.query.limit(2).offset(0).all()
        results = Weather2.query.offset(0).all()

        json_results = []

        for result in results:
            d={
                'temp': result.temp,
                'humidity': result.humidity,
                'windSpeed': result.windSpeed,
                'windDirection':result.windDirection}
            json_results.append(d)

        return jsonify(items=json_results)
        #return 'i guess it works ?!?!'

    else: # must be a post
        t = request.args.get('t')
        h = request.args.get('h')
        wS = request.args.get('ws')
        wD = request.args.get('wd')
        
        print "This is temp: %s" %t
        print "This is humidity: %s" %h
        print "This is windSpeed: %s" %wS
        print "This is windDirection: %s" %wD
        #result = Weather.query.add(temp=temp,humidity=humidity,windSpeed=windSpeed,windDirection=windDirection)
        query = 'INSERT INTO wsT (temp,humidity,windSpeed,windDirection) values (\'%s\',\'%s\',\'%s\',\'%s\')' %(t,h,wS,wD)
        Weather2.query.from_statement(str(query)).all()
        Weather2.flush()

        return "does this give 200 ?"

@app.route('/weather4/', methods = ['GET', 'POST'])
def weather4():
    #print 'we are about to hit GET'
    if request.method == 'GET':
 
        results = Weather4.query.all()
 

        json_results = []

        for result in results:
            d= {
                    'DateRecorded':result.DateRecorded,
                    'DHTCelcius':result.DHTCelcius,
                    'DHTFarenheight':result.DHTFarenheight,
                    'DHTHeatIndex':result.DHTHeatIndex,
                    'DHTHumidity':result.DHTHumidity,
                    'BaroCelcius':result.BaroCelcius,
                    'BaroPressure':result.BaroPressure}

            json_results.append(d)


        return jsonify(items=json_results)

    elif request.method == 'POST':
        DHT_c = request.args.get('DHTCelcius')
        DHT_f = request.args.get('DHTFarenheight')
        DHT_hi = request.args.get('DHTHeatIndex')
        DHT_h = request.args.get('DHTHumidity')
        BARO_c = request.args.get('BaroCelcius')
        BARO_p = request.args.get('BaroPressure')

        query = 'INSERT INTO wsT4 (DHTCelcius,DHTFarenheight,DHTHeatIndex,DHTHumidity,BaroCelcius,BaroPressure) values (\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')' %(DHT_c,DHT_f,DHT_hi,DHT_h,BARO_c, BARO_p)
        Weather4.query.from_statement(str(query)).all()
        Weather4.flush()

    else:
        return 'INVALID METHOD'


@app.route('/weatherToday/', methods = ['GET'])
@cross_origin()
def weatherToday():
    currentDate = date.today()
    print "This is our current: %s" %currentDate
  

    if request.method == 'GET':
        #results = Weather4.query.all()
        #results = Weather4.query.filter(Weather4.DateRecorded > '2015-06-01')
        results = Weather4.query.filter(Weather4.DateRecorded > "%s" %currentDate) 
        #Fri, 22 May 2015 04:34:47 GMT

        json_results = []
        i=0
        for result in results:
            d= {
                    'x':i, 
                    'DateRecorded':result.DateRecorded,
                    'DHTCelcius':result.DHTCelcius,
                    'DHTFarenheight':result.DHTFarenheight,
                    'DHTHeatIndex':result.DHTHeatIndex,
                    'DHTHumidity':result.DHTHumidity,
                    'BaroCelcius':result.BaroCelcius,
                    'BaroPressure':result.BaroPressure}

            json_results.append(d)
            i += 1

        return jsonify(items=json_results)

    else:
        return "INVALID METHOD"


#app.route('/weatherMinusDays/<int:days1>', methods = ['GET'])
@app.route('/wmd/<int:days1>', methods = ['GET'])
@cross_origin()
def getWeather(days1):
    print "days: %s" %days1
    currentDate = date.today() 
    print "current Date: %s" %currentDate
    previousDate = currentDate - timedelta(days=days1)
    print 'previousDate: %s' %previousDate


    if request.method == 'GET':
        results = Weather4.query.filter(Weather4.DateRecorded > "%s" %previousDate).order_by(Weather4.DateRecorded.asc())
        #results = Weather4.query.filter(Weather4.DateRecorded > "%s" %previousDate).order_by(Weather4.DateRecorded.desc())

        json_results = []
        i=0
        for result in results:
            d= {
                    'x': i,
                    'DateRecorded':result.DateRecorded,
                    'DHTCelcius':result.DHTCelcius,
                    'DHTFarenheight':result.DHTFarenheight,
                    'DHTHeatIndex':result.DHTHeatIndex,
                    'DHTHumidity':result.DHTHumidity,
                    'BaroCelcius':result.BaroCelcius,
                    'BaroPressure':result.BaroPressure}

            json_results.append(d)
            i +=1

        return jsonify(items=json_results)

    else:
        return "INVALID METHOD"



if __name__ == '__main__':
 #app.run(debug=True)
 app.run(host='0.0.0.0')


# curl -X GET 127.0.0.1:5000/weather2/
#select * from wsT4 where DHTCelcius = (select max(DHTCelcius));
#select * from wsT4 where DHTCelcius = (select min(DHTCelcius));