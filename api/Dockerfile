FROM python:2-onbuild

# Add in the routes.py file

ADD routes.py /

# Install required libraries

RUN pip install -r requirements.txt

#RUN pip install flask
#RUN pip install sqlalchemy

#Open up 9000

EXPOSE 5000

#Execute

CMD [ "python", "./routes.py" ]