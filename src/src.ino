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
int state;             // int yerine yukardaki enum tipinde olmalı

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
  double dbl_altitude = (double)altitude / 10; // Double görünsün istiyoruz

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

  // Her şeyi bir string'de toplayıp en son yollamamızın sebebi packet loss gibi bir problemin önüne geçmek
  auto comma  = String(",");
  auto container_packet = String(team_id);     container_packet += comma;
  container_packet += String(mission_time);    container_packet += comma;
  container_packet += String(packet_count);    container_packet += comma;
  container_packet += String("C");             container_packet += comma; // "C" for container
  container_packet += String("S");             container_packet += comma; // "S" for simulation
  container_packet += String("1,1");           container_packet += comma; // released both
  container_packet += String(dbl_altitude, 1); container_packet += comma;
  container_packet += String(temp, 1);         container_packet += comma;
  container_packet += String(voltage, 2);      container_packet += comma;
  container_packet += String(gps_time);        container_packet += comma;
  container_packet += String(gps_lati, 4);     container_packet += comma;
  container_packet += String(gps_long, 4);     container_packet += comma;
  container_packet += String(gps_alti, 1);     container_packet += comma;
  container_packet += String(gps_sats);        container_packet += comma;
  container_packet += String(state);           container_packet += comma;
  container_packet += String(packet_count);    container_packet += comma;
  container_packet += String(packet_count);

  auto sp1_packet = String(team_id);     sp1_packet += comma;
  sp1_packet += String(mission_time);    sp1_packet += comma;
  sp1_packet += String(packet_count);    sp1_packet += comma;
  sp1_packet += String("SP1");           sp1_packet += comma; // "SP1" for science payload 1
  sp1_packet += String(dbl_altitude, 1); sp1_packet += comma;
  sp1_packet += String(temp, 1);         sp1_packet += comma;
  sp1_packet += String("140.3");

  auto sp2_packet = String(team_id);     sp2_packet += comma;
  sp2_packet += String(mission_time);    sp2_packet += comma;
  sp2_packet += String(packet_count);    sp2_packet += comma;
  sp2_packet += String("SP2");           sp2_packet += comma;
  sp2_packet += String(dbl_altitude, 1); sp2_packet += comma;
  sp2_packet += String(temp, 1);         sp2_packet += comma;
  sp2_packet += String("120.5");


  Serial.println(container_packet);
  Serial.println(sp1_packet);
  Serial.println(sp2_packet);

  packet_count += 1;

  delay(1000); // 1 sn bekle.
}
