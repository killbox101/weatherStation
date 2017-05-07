#FROM armhf/python
FROM hypriot/rpi-python

# Add in the routes.py file

ADD routes.py /
ADD requirements.txt /
# Install required libraries


#RUN cd ../
#RUN ls
RUN apt-get -qq  update
RUN apt-get -y install python-mysqldb
#RUN pip list
RUN pip install -r ../requirements.txt

#RUN pip install flask
#RUN pip install sqlalchemy


#Open up 9000

EXPOSE 5000

#Execute

CMD ["python", "../routes.py" ]
