#pragma once

class Resources {
public:
	float water;
	float energy;
	float materials;

	Resources ();
	Resources (float w, float e, float m);
	Resources add (Resources res);
	Resources subtract (Resources res);
	Resources multiply (float k);
	Resources multiply (Resources res);
	bool check_capacity (Resources res);
	void cutoff (Resources res);
};