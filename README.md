
# Лабораторная работа № 2 
## 1) Изучение и написание матриц перемещения, вращения и изменения размера объекта:
### Инициализация переменной для изменения 
```с++
float Scale = 0.0f;
```
### Задание матриц
```с++

    //Базовая матрица
    glm::mat4 WorldMat = glm::mat4{ 1.0f };

    //матрица перемещения
    glm::mat4 WorldTrans{
    1.0f, 0.0f,  0.0f, 0.0f,
    0.0f, 1.0f,  0.0f, 0.0f,
    0.0f, 0.0f,  1.0f, 0.0f,
    sinf(Scale), 0.0f, 0.0f, 1.0f
    };

    //Матрица вращения
    glm::mat4 WorldRotate{
    cosf(Scale),  sinf(Scale), 0.0f, 0.0f,
    -sinf(Scale), cosf(Scale), 0.0f, 0.0f,
     0.0f,        0.0f,        1.0f, 0.0f,
     0.0f,        0.0f,        0.0f, 1.0f
    };

    //Матрица изменения масштаба
    glm::mat4 WorldScale{
     abs(sinf(Scale)), 0.0f, 0.0f, 0.0f,
     0.0f, abs(cosf(Scale)), 0.0f, 0.0f,
     0.0f, 0.0f, abs(sinf(Scale)), 0.0f,
     0.0f, 0.0f, 0.0f, 1.0f
     };
     
     Scale += 0.001f;
``` 

Для постоянного обновления значения Scale, в функции отрисовки необходимо добавить вызов функции:
```c++
glutPostRedisplay();
```

## 2) Проекция перспективы
### инициализвция необходимых переменных
```с++
const float ar = 1024 / 768;
const float zNear = 0.005;
const float zFar = 80;
const float zRange = zNear-zFar;
const float tanHalfFOV = tanf(glm::radians(20 / 2.0));
```
###  Задание матрицы перспективы
```с++
glm::mat4 WorldPerspect{
        1.0f / (tanHalfFOV * ar), 0.0f,             0.0f, 0.0f,
        0.0f,                1.0f / tanHalfFOV,      0.0f, 0.0f,
        0.0f, 0.0f,          (-zN - zF) / zR,  2.0f * zF * zN / zR,
        0.0f, 0.0f,          1.0f,              0.0f
    };
```
## 3) Пространство камеры
###  Задание системы координат камеры. Позиция камеры и 3 вектора камеры
```с++
 glm::vec3 cameraPos = glm::vec3(0.3f, 0.3f, 0.3f);

 glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
 glm::vec3 cameraTarget = glm::vec3(0.45f, 0.0f, 1.0f);
 glm::vec3 cameraRight = glm::cross(cameraUp, cameraTarget);
```
###  Задание матрицы изменения позиции камеры
```с++
glm::mat4 WorldCamTrans{
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
       -cameraPos.x, -cameraPos.y, -cameraPos.z, 1.0f,
    };
```
### Задание матрицы вращения камеры
```с++
glm::vec3 N = cameraTarget;
    N = glm::normalize(N);
    glm::vec3 U = cameraUp;
    U = glm::normalize(U);
    U = glm::cross(U, cameraTarget);
    glm::vec3 V = glm::cross(N, U);
    
    glm::mat4 WorldCamRotate{
        U.x,V.x,N.x,0.0f,
        U.y,V.y,N.y,0.0f,
        U.z,V.z,N.z,0.0f,
        0.0f,0.0f,0.0f,1.0f,
    };
```
## 4) Применение всех преобразований
```с++
glm::mat4 WorldMat2 = WorldPerspect * WorldCamRotate *          WorldCamTrans * WorldScale * WorldRotate * WorldTrans * WorldMat;
glLoadMatrixf(static_cast<const float*>(glm::value_ptr(WorldMat2)));
```
