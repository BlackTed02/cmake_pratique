#pragma once
#include "pch.h"

#ifdef USING_EDITOR
#include "imgui-SFML.h"
#include "imgui.h"
#endif 

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define PI 3.141592f
#define DEG_TO_RAD PI / 180.f
#define RAD_TO_DEG 180.f / PI
#define EPSILON (float)1e-6

void InitTools(); 
void RestartClock(); 
float GetDeltaTime(); 
bool IsMouseHasFocus(sf::RenderWindow* _w);
bool CustomKeyboardIsKeyPressed(sf::Keyboard::Scancode _key, sf::RenderWindow* _w); 
float GetSqrMagnitudeBetweenVector(sf::Vector2f _vec1, sf::Vector2f _vec2);
sf::Time GetTime();
int RandomInt(int min, int max);
std::string ConvertToString(char* charArray);
std::string ConvertToString(const char* charArray);
std::string GetLastElement(const std::string& path);
std::string MakeRelativePath(const std::string& absolutePath, const std::string& basePath);
sf::Vector2f PolarCord(sf::Vector2f _vec1);
void CopyFile(const std::string& source, const std::string& destination);
float Deg2Rad(float _deg);
sf::Vector2f RotatePoint(sf::Vector2f _center, sf::Vector2f _posBeforeRotation, float _angle);
inline float DotProduct(sf::Vector2f _v1, sf::Vector2f _v2) { return _v1.x * _v2.x + _v1.y * _v2.y; }
float GetSqrMagnitude(sf::Vector2f const& _a);
float GetMagnitude(sf::Vector2f const& _a);
sf::Vector2f Normalize(sf::Vector2f const& _vec);
sf::Vector2f CreateVectorWithVector(sf::Vector2f const& _v1, sf::Vector2f const& _v2);
void PointSegmentDistance(sf::Vector2f const& _p, sf::Vector2f const& _a, sf::Vector2f const& _b, float& _distSqr, sf::Vector2f& _contact);
