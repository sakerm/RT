#include "../includes/rt.h"

static double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

static double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

static double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15;
	u = (h < 8) ? x : y;
	v = (h < 4) ? y : (h == 12 || h == 14) ? x : z;
	return ((((h&1) == 0) ? u : -u) + (((h&2) == 0) ? v : -v));
}

static int	p[512];

static int	permutation[] = {151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

double	ImprovedNoise(double x, double y, double z)
{
	int		X;
	int		Y;
	int		Z;
	double	u;
	double	v;
	double	w;
	int		A;
	int		AA;
	int		AB;
	int		B;
	int		BB;
	int		BA;
	static int		i = 0;

	if (i == 0)
	{
		while (i < 256)
		{
			p[256 + i] = p[i] = permutation[i];
			i++;
		}
	}
	X = (int)floor(x) & 255;
	Y = (int)floor(y) & 255;
	Z = (int)floor(z) & 255;
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	u = fade(x);
	v = fade(y);
	w = fade(z);
	A = p[X] + Y;
	AA = p[A] + Z;
	AB = p[A+1] + Z;
	B = p[X+1] + Y;
	BA = p[B] + Z;
	BB = p[B+1] + Z;
	return (lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x-1, y, z)),
							lerp(u, grad(p[AB], x, y-1, z), grad(p[BB], x-1, y-1, z))),
					lerp(v, lerp(u, grad(p[AA+1], x, y, z-1), grad(p[BA+1], x-1, y, z-1)),
							lerp(u, grad(p[AB+1], x, y-1, z-1), grad(p[BB+1],
								x-1, y-1, z-1)))));
}

double	noise(double x, double y, double z, double freq)
{
	double	x1;
	double	y1;
	double	z1;

	x1 = 0.707 * x - 0.707 * z;
	z1 = 0.707 * x + 0.707 * z;
	y1 = 0.707 * x1 + 0.707 * y;
	x1 = 0.707 * x1 - 0.707 * y;
	return (ImprovedNoise(freq * x1 + 100, freq * y1, freq * z1));
}

double	turbulence(double x, double y, double z, double freq)
{
	double	t = -0.5;
	while (freq <= W/12)
	{
		t += abs(noise(x, y, z, freq) / freq);
		freq *= 2;
	}
	return (t);
}

double	stripes(double x, double f)
{
	double	t;

	t = 0.5 + 0.5 * sin(f * 2 * 3.141592 * x);
	return (t * t - 0.5);
}

double	f(double x, double y, double z, int text)
{
	if (text == 1)
		return (1 * stripes(x + 2 * turbulence(x, y, z, 1), 2));
	else if (text == 2)
		return (0.01 * stripes(x + 2 * turbulence(x, y, z, 1), 8));
	else if (text == 3)
		return (0.1 * stripes(x + 2 * turbulence(x, y, z, 2), 12));
	else if (text == 4)
		return (0.03 * noise(8 * x, 8 * y, 8 * z, 1));
	else if (text == 5)
		return (0.03 * noise(8 * x, 8 * y, 8 * z, 1.5));
	return (1);
}

t_vec	text1(t_vec n, int text)
{
	double	f0;
	double	fx;
	double	fy;
	double	fz;

//	printf("\n%f\n", n.x);
//	printf("%f\n", n.y);
//	printf("%f\n", n.z);
	f0 = f(n.x, n.y, n.z, text);
	fx = f(n.x + 0.0001, n.y, n.z, text);
	fy = f(n.x, n.y + 0.0001, n.z, text);
	fz = f(n.x, n.y, n.z + 0.0001, text);
	n.x -= (fx - f0) / 0.0001;
	n.y -= (fy - f0) / 0.0001;
	n.z -= (fz - f0) / 0.0001;
	normalize(&n);
//	printf("%f\n", n.x);
//	printf("%f\n", n.y);
//	printf("%f\n", n.z);
	return (n);
}
