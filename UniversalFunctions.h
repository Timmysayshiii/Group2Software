#ifndef UniversalFunctions_h
#define UniversalFunctions_h

	void findStream(char stream[]);
	void storeCartesian(void);
  void parseGGA(char GGA[]);
	void extractTime(void);
	void skipName(void);
	void extractLatitude(void);
	double convertWholeNumber(char numberstring[]);
	void extractlatDirection(void);
	void extractlongDirection(void);
	void extractLongitude(void);
	void extractLongitude(void);
	void extractqualityofFix(void);
	void extractnumofSatellites(void);
	void extractHDOP(void);
	void extractAltitude(void);
	void extractaltitudeUnit(void);
	void extractgeoidSeperation(void);
	void extractgeoidsepUnit(void);
  void extractdiffcorrectionAge(void);
  void extractdiffStationIDandChecksum(void);
  void encodeGGA(void);
	
#endif
