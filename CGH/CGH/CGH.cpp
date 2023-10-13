#include <iostream>
#include <string>
#include <fstream>
#include <omp.h>
#include <filesystem>
#include <sstream>
#include <psl.h>

int main()
{
    using namespace std;
	using namespace wfl;
	using namespace psl;

	Start();
	wfl::SetNumThreads();

	/// frame buffer settings
	const double	p	= 7.56e-6;	///< sampling pitch (= SLM pitch)
	const int		nx	= 2048;		///< sampling number (x-axis)
	const int		ny	= 2048;		///< sampling number (y-axis)
	const double	lambda[] = { 638e-9, 518e-9, 448e-9 };	///< RGB wavelengths

	/// object model settings
	const string	objFile			= "model\\dice.mqo";					///< object model file
	const double	objWidth[]		= { 4.06e-3, 5.0e-3, 5.781e-3 };		///< object model sizes for RGB
	const double	objPosition[]	= { 131.8403e-3, 200e-3, 267.3828e-3 };	///< distances between focal and imaging plane for RGB

	/// diffraction settings
	const double	theta[] = { -2.64843, -1.0551, 0.833828 };	///< diffraction angles of 0th order light for RGB
	const double	x		= 0;								///< reconstruction position (x)
	const double	y		= 0;								///< reconstruction position (y)
	const double	f		= 150e-3;							///< focal length of lens

	/// shader settings
	const double	gamma	= 0.01;					///< 補正制限値
	const double	env		= 0.1;					///< 環境光比率
	const Vector	light(-0.408, -0.408, -0.816);	///< 照明光の進行方向ベクトル


	/// UV texture mapping
	const string textureDirectory = "model\\";
	vector<char*> textureFiles;
	GetTextureNamesMqo(objFile.c_str(), textureFiles);

	/// output directory
	const filesystem::path path = filesystem::path("results");
	if (!filesystem::exists(path))
	{
		filesystem::create_directory(path);
	}

	IndexedFaceSet obj;
	obj.LoadMqo(objFile.c_str());	///< loading object model file
	obj.Localize();					///< place the object at the origin
	obj += Point(0, 0, 0);			///< object position setting
	obj.AutoNormalVector();			///< normal vector setting

	for (auto c = 1; c <= 3; c++)
	{
		/// object model size setting
		obj.SetWidth(objWidth[c - 1]);

		/// Lambert shader
		TfbLambertShading shading(gamma, light, (ColorMode)c, env);

		/// UV texture mapping
		TfbUvMapping texture(textureFiles, textureDirectory.c_str(), 1.0, (ColorMode)c);

		/// frame buffer
		WaveField frame(nx, ny, p, p, lambda[c - 1]);
		frame.Clear();
		frame.SetOrigin(Point(0, 0, 0));

		/// silhouette masking
		PaintObjectSilhouette(frame, obj);

		SurfaceBuilder sb(frame);
		sb.SetShader(shading);						///< shader object
		sb.SetTexture(texture);						///< UV texture mapping
		sb.AddObjectFieldSb(frame, obj, 1, true);	///< calculate image hologram

		frame.ExactAsmProp(-objPosition[c - 1]);	///< backpropagation to focal plane
		frame.Fft(+1);								///< inverse FFT
		frame.SetPx(p);
		frame.SetPy(p);

		/// superimposing of plane wave
		const Vector s = CRMatrixZ(-45 * DEG) * CRMatrixY(theta[c - 1] * DEG) * Vector(x / f, y / f, sqrt(1 - (x * x + y * y) / (f * f)));
		frame.MultiplyPlaneWave(s, 0.0);

		/// binary hologram
		frame.Add(frame.ConvToConjugate());	///< make real number by adding complex conjugate
		if (c == RED)	frame.SaveAsGrayBmp(string("results/binary-red.bmp").c_str(), REAL, 1, 1);
		if (c == GREEN)	frame.SaveAsGrayBmp(string("results/binary-green.bmp").c_str(), REAL, 1, 1);
		if (c == BLUE)	frame.SaveAsGrayBmp(string("results/binary-blue.bmp").c_str(), REAL, 1, 1);
	}

	return 0;
}
