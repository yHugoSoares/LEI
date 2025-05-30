import pandas as pd
import pymysql

# Extração do CSV
df_csv = pd.read_csv("lisboa_stand.csv", encoding="latin1")

# Extração do MySQL
conn = pymysql.connect(host="porto_stand_db", user="user", password="pass", database="bycar_porto")
df_mysql = pd.read_sql("SELECT * FROM reservas", conn)

# Transformação: Unificar campos de data
df_csv['data_checkin'] = pd.to_datetime(df_csv['data_checkin'], format="%d/%m/%Y")
df_mysql['data_inicio'] = pd.to_datetime(df_mysql['data_inicio'])