// CanSat Dummy telemetry generator
// Abdulkerim Güven, 2020-02

const int team_id = 0;
unsigned int mission_time; // in seconds
unsigned int packet_count;
unsigned int altitude; // resolution is 0.1 meters.
unsigned int pressure; // resolution is 1 pascal.
int temp;			   // resolution is 0.1 centigrade.
unsigned int voltage;  // resolution is 0.01 volts.

enum software_state
{
	boot,
	idle,
	launch_detect,
	// TODO: Add more variants, think about the existent ones.
};

// TODO: Everything.
void setup()
{
	// put your setup code here, to run once:
	mission_time = 0;
}

void loop()
{
	unsigned int gps_time; // UTC, resolution is 1 second.
	unsigned int gps_lati; // resolution is 0.0001
	unsigned int gps_long; // resolution is 0.0001
	unsigned int gps_alti; // meters above mean sea level, resolution is 0.1m
	unsigned int gps_sats; // number of GPS satellites
	double air_speed;	  // Air speed relative to payload in m/s
	software_state state;
	double particle_count; // mg/m^3
}

void print_data()
{
	// We'll call this routine every second.
	packet_count++;
}