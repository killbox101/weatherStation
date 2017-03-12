#!/bin/bash

#service Name

service="routes.py"
echo="$service"

if (( $(ps -ef |grep -v grep | grep $service | wc -l ) > 0 ))
then 
echo "$service is running"
else 
echo "$service not running" 
. venv/bin/activate
echo "step 1 complete"
python routes.py
echo "step 2 complete"
fi





