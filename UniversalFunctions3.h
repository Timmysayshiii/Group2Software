#ifndef UniversalFunctions3_h
#define UniversalFunctions3_h

	void findStream3(char stream[]);
//	void storeCartesian3(void);
  void parseGGA3(char GGA[]);
	void extractTime3(void);
	void skipName3(void);
	void extractLatitude3(void);
	double convertWholeNumber3(char numberstring[]);
	void extractlatDirection3(void);
	void extractlongDirection3(void);
	void extractLongitude3(void);
	void extractLongitude3(void);
	void extractqualityofFix3(void);
	void extractnumofSatellites3(void);
	void extractHDOP3(void);
	void extractAltitude3(void);
	void extractaltitudeUnit3(void);
	void extractgeoidSeperation3(void);
	void extractgeoidsepUnit3(void);
  void extractdiffcorrectionAge3(void);
  void extractdiffStationIDandChecksum3(void);
  void encodeGGA3(void);
	
#endif
