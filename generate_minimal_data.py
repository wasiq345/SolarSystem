from  astroquery.jplhorizons import Horizons
from datetime import datetime, timedelta

today = datetime.now()
tomorrow = today + timedelta(days=1)

today_str = today.strftime("%Y-%m-%d")
tomorrow_str = tomorrow.strftime("%Y-%m-%d")

obj = Horizons(id='399', location='@sun', epochs={'start': today_str, 'stop': tomorrow_str, 'step': '1d'})
data = obj.ephemerides()

# set Data to be written to file
ra = data['RA'][0]
dec = data['DEC'][0]
delta = data['delta'][0]

# write to file 
with open('earth_data_minimal.txt', 'w') as file:
    file.write(f"{ra}\n")
    file.write(f"{dec}\n")
    file.write(f"{delta}\n")




