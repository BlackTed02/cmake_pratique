#include "pch.h"
#include "tools.h"

sf::Clock sfClock;
sf::Time sfTime;

void InitTools()
{
	sfClock = sf::Clock();
	sfTime = sf::Time();
	srand(time(NULL));
}

void RestartClock()
{
	sfTime = sfClock.restart();
}

float GetDeltaTime()
{
	return sfTime.asSeconds();
}

bool IsMouseHasFocus(sf::RenderWindow* _w)
{
	sf::Vector2i mouseCursor = sf::Mouse::getPosition();
	if (mouseCursor.x >= 0 && mouseCursor.x <= _w->getSize().x && mouseCursor.x >= 0 && mouseCursor.y <= _w->getSize().y) return true;
	else return false;
}

bool CustomKeyboardIsKeyPressed(sf::Keyboard::Scancode _key, sf::RenderWindow* _w)
{
	if (_w->hasFocus()) {
		return sf::Keyboard::isKeyPressed(_key);
	}
	return false;
}

float GetSqrMagnitudeBetweenVector(sf::Vector2f _vec1, sf::Vector2f _vec2)
{
	sf::Vector2f vector(_vec2.x - _vec1.x, _vec2.y - _vec1.y);
	float sqrMagnitude = (vector.x * vector.x) + (vector.y * vector.y);
	return sqrMagnitude;
}

sf::Time GetTime()
{
	return sfTime;
}

int RandomInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

// Fonction pour convertir un char* en std::string

std::string ConvertToString(char* charArray) 
{
	if (charArray) {
		return std::string(charArray);
	}
	else {
		return std::string();
	}
}

std::string ConvertToString(const char* charArray)
{
	if (charArray) {
		return std::string(charArray);
	}
	else {
		return std::string();
	}
}

std::string GetLastElement(const std::string& path)
{
	return std::filesystem::path(path).filename().string();
}
 
std::string MakeRelativePath(const std::string& absolutePath, const std::string& basePath)
{
	// On suppose que les chemins fournis sont cohérents en termes de casse
	// Vérifiez si basePath est un préfixe d'absolutePath
	if (absolutePath.find(basePath) == 0)
	{
		// Créez le chemin relatif en enlevant la partie basePath de absolutePath
		std::string relativePath = absolutePath.substr(basePath.length());

		// Remplacez les antislashs par des barres obliques
		std::replace(relativePath.begin(), relativePath.end(), '\\', '/');

		// Préfixez le chemin relatif avec ".." pour revenir au répertoire de base-
		return ".." + relativePath;
	}

	// Si basePath n'est pas un préfixe, retournez le chemin absolu original
	return absolutePath;
}

void CopyFile(const std::string& source, const std::string& destination)
{
	std::ifstream src(source, std::ios::binary);
	std::ofstream dest(destination, std::ios::binary);

	if (!src || !dest) {
		throw std::ios_base::failure("Erreur lors de l'ouverture des fichiers");
	}

	dest << src.rdbuf();
	src.close();
	dest.close();
}

float Deg2Rad(float _deg)
{
	return _deg * (3.14159265359 / 180);
}

sf::Vector2f RotatePoint(sf::Vector2f _center, sf::Vector2f _posBeforeRotation, float _angle)
{
	float radAngle = _angle * DEG_TO_RAD;
	float sin = std::sin(radAngle);
	float cos = std::cos(radAngle);

	_posBeforeRotation.x -= _center.x;
	_posBeforeRotation.y -= _center.y;

	float rotatedX = _posBeforeRotation.x * cos - _posBeforeRotation.y * sin;
	float rotatedY = _posBeforeRotation.x * sin + _posBeforeRotation.y * cos;

	return sf::Vector2f(rotatedX + _center.x, rotatedY + _center.y);
}

float GetSqrMagnitude(sf::Vector2f const& _a)
{
	return (_a.x * _a.x) + (_a.y * _a.y);
}

float GetMagnitude(sf::Vector2f const& _a)
{
	return sqrtf(GetSqrMagnitude(_a));;
}

sf::Vector2f Normalize(sf::Vector2f const& _vec)
{
	float magnitude = GetMagnitude(_vec);
	if (magnitude < EPSILON) {
		return _vec;
	}
	return sf::Vector2f(_vec.x / magnitude, _vec.y / magnitude);
}

sf::Vector2f CreateVectorWithVector(sf::Vector2f const& _v1, sf::Vector2f const& _v2)
{
	return sf::Vector2f(_v2.x - _v1.x, _v2.y - _v1.y);;
}

void PointSegmentDistance(sf::Vector2f const& _p, sf::Vector2f const& _a, sf::Vector2f const& _b, float& _distSqr, sf::Vector2f& _contact)
{
	sf::Vector2f const ab(_b - _a);
	sf::Vector2f const ap(_p - _a);

	float const dot = DotProduct(ab, ap);
	float const sqrMagAb = GetSqrMagnitude(ab);

	float const d = dot / sqrMagAb;

	if (d < 0.f)
	{
		_contact = _a;
	}
	else if (d > 1.f)
	{
		_contact = _b;
	}
	else {
		_contact = _a + ab * d;
	}

	_distSqr = GetSqrMagnitudeBetweenVector(_contact, _p);
}

sf::Vector2f PolarCord(sf::Vector2f _vec1)
{
	sf::Vector2f tempVec;
	tempVec.x = sqrt((_vec1.x * _vec1.x) + (_vec1.y * _vec1.y));
	tempVec.y = atan2(_vec1.y, _vec1.x);
	_vec1 = tempVec;
	return _vec1;
}
