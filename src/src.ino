// CanSat Dummy telemetry generator
// Abdulkerim Güven, 2020-02

/*
  enum software_state
  {
  boot,
  idle,
  launch_detect,
  // TODO: Add more variants, think about the existent ones.
  };
*/

const int team_id = 1111;
int mission_time; // in seconds
int packet_count;
long randNum;
int altitude = 0;      // resolution is 0.1 meters.
int pressure = 0;      // resolution is 1 pascal.
double temp = 0;       // resolution is 0.1 centigrade.
double voltage = 0;    // resolution is 0.01 volts.
int gps_time = 0;      // UTC, resolution is 1 second.
double gps_lati = 0;   // resolution is 0.0001 (10^-4)
double gps_long = 0;   // resolution is 0.0001 (10^-4)
double gps_alti = 0;   // meters above mean sea level, resolution is 0.1m
int gps_sats = 0;      // number of GPS satellites
double air_speed;      // Air speed relative to payload in m/s
int state;             // int yerine yukardaki enum tipinde olmalı
double particle_count; // mg/m^3

// TODO: Everything.
void setup()
{
  Serial.begin(9600);

  mission_time = 0;

  // Okulun koordinatları
  gps_lati = 39.8192;
  gps_long = 32.5622;

  temp = 22.1;    // TODO Gerçek değer nasıl olur?
  voltage = 5.01; // TODO Gerçek değer nasıl olur?

  randomSeed(analogRead(0));
}

void loop()
{
  randNum = random(10000, 100000);

  mission_time += 1;

  // resolution is 0.1 meters.
  double aux_alti = altitude;
  altitude += (randNum % 15);
  double daltitude = (double)altitude / 10; // Double görünsün istiyoruz

  // Basınç hesaplama formulünü bozup bu hale getirdim.
  pressure = 101325 * (0.9999 * altitude);
  pressure = pressure >= 0 ? pressure : -1 * pressure; // Pozitif olsun.
  pressure %= 10000;

  gps_time = mission_time; // TODO

  // Şimdilik altitude ile gps aynı olsun.
  gps_alti = altitude;

  // Bunun sayısı aslında önemli değil ama gittikçe artırıyorum.
  gps_sats += 2;

  // Yükseklik değişiminden bir şeyler salladım.
  air_speed = (altitude - aux_alti) * 2;

  // TODO Daha uçuş phase'lerini eklemedim ondan hep 0.
  state = 0;

  // Bunun ne olacağını bilemiyoruz.
  particle_count = randNum / 1000.0; // mg/m^3

  Serial.print(team_id); // team id
  Serial.print(",");
  Serial.print(mission_time); // mission time
  Serial.print(",");
  Serial.print(packet_count); // packet count
  Serial.print(",");
  Serial.print(daltitude, 1); // altitude
  Serial.print(",");
  Serial.print(pressure); // pressure
  Serial.print(",");
  Serial.print(temp, 1); // temp
  Serial.print(",");
  Serial.print(voltage, 2); // voltage
  Serial.print(",");
  Serial.print(gps_time); // gps_time
  Serial.print(",");
  Serial.print(gps_lati, 4); // gps_lati
  Serial.print(",");
  Serial.print(gps_long, 4); // gps_long
  Serial.print(",");
  Serial.print(gps_alti, 1); // gps_alti
  Serial.print(",");
  Serial.print(gps_sats); // gps_sats
  Serial.print(",");
  Serial.print(air_speed); // air_speed
  Serial.print(",");
  Serial.print(state); // software_state
  Serial.print(",");
  Serial.print(particle_count, 3); // particle_count
  Serial.println();

  packet_count += 1;

  delay(1000); // 1 sn bekle.
}
