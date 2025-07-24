from astroquery.jplhorizons import Horizons
import matplotlib.pyplot as plt
from datetime import datetime, timedelta

# Generate Julian dates for past 7 days
today = datetime.now()
dates = [(today - timedelta(days=i)).strftime("%Y-%m-%d") for i in range(7)]

ra_values = []
dec_values = []
delta_values = []
date_labels = []

for date in dates:
    # Convert date to Julian date 
    from astropy.time import Time
    t = Time(date)
    jd = t.jd

    obj = Horizons(id='399', location='@sun', epochs=[jd])
    data = obj.ephemerides()
    
    ra_values.append(data['RA'][0])
    dec_values.append(data['DEC'][0])
    delta_values.append(data['delta'][0])
    date_labels.append(date)

# Reverse the order for plotting
date_labels = date_labels[::-1]  
ra_values = ra_values[::-1]
dec_values = dec_values[::-1]
delta_values = delta_values[::-1]

# Plot RA
plt.figure(figsize=(8,4), facecolor='none')
plt.plot(date_labels, ra_values, marker='o', color='cyan')
plt.xticks(rotation=45, color='white')
plt.yticks(color='white')
plt.title("Earth Right Ascension (past 7 days)", color='white')
plt.gca().set_facecolor('black')
plt.tight_layout()
plt.savefig("graphics/earth_ra.png", transparent=True)
plt.close()
