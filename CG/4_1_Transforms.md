# Computer Graphics: Transforms (변환)

**강의:** Computer Graphics - Transforms (Sung Soo Hwang)

## 1. 개요 (Introduction)
- **변환(Transform)**: 점, 벡터, 색상 등의 엔티티를 변환하는 연산으로, 객체, 조명, 카메라의 위치 설정, 모양 변경, 애니메이션에 사용됨.
- **행렬 곱셈(Matrix Multiplication)**: 
  - 여러 변환을 결합하여 한 번의 연산으로 적용 가능 ($M_{total} = M_{proj} \cdot M_{view} \cdot M_{model}$)
  - GPU는 동시에 여러 데이터의 연산을 수행하므로 행렬-벡터 곱셈의 병렬 처리에 매우 적합함.
- **선형 변환(Linear Transform)**:
  - 벡터의 덧셈과 스칼라 곱셈을 보존함.
  - 조건 1: $f(\vec{x} + \vec{y}) = f(\vec{x}) + f(\vec{y})$
  - 조건 2: $kf(\vec{x}) = f(k\vec{x})$
  - $f(x)=2x+3$ 같은 이동(Translation)은 선형 변환이 아니라는 문제가 있음.

## 2. 동차 좌표계 (Homogeneous Coordinates)
- 선형 변환과 이동(Translation)을 함께 결합하기 위해 4차원 벡터 형식인 동차 좌표계를 사용: $(x, y, z, 1)$
- **방향 벡터(Direction Vector)**: $\vec{v} = (v_x, v_y, v_z, 0)^T$
- **점(Point)**: $\vec{v} = (v_x, v_y, v_z, 1)^T$

## 3. 기본 변환 (Basic Transforms)
- **이동 (Translation)**: 지정된 위치만큼 더함. 역행렬은 이동값의 부호를 반대로 한 것.
- **회전 (Rotation)**: X, Y, Z축 기준의 회전. 모든 회전 행렬의 행렬식(Determinant)은 1이고, 직교 행렬(Orthogonal)임. 역행렬은 전치 행렬(Transpose)과 같음 ($R^{-1}(\phi) = R(-\phi) = R^T(\phi)$).
- **크기 변환 (Scaling)**: 객체 확대/축소. 역행렬은 각 축소/확대 비율의 역수($1/s_x, 1/s_y, 1/s_z$).
- **전단 (Shearing)**: 객체를 비틀어 변형. 부피를 보존하므로 행렬식은 1.
- **반사 (Reflection)**: 원본 객체의 크기는 유지하며 특정 축에 대한 반전을 의미(예: XY 평면 반사 시 Z축 부호 반전).

## 4. 변환의 결합 (Concatenation of Transforms)
- 행렬 곱셈은 **교환 법칙이 성립하지 않으므로(Noncommutative)** 곱하는 순서가 매우 중요함.
- 일반적인 변환 적용 순서: $C = T \cdot R \cdot S$ (크기 변환 $\rightarrow$ 회전 $\rightarrow$ 이동 순서로 벡터에 적용)

## 5. 투영 (Projections)
- **직교 투영 (Orthographic Projection)**:
  - 아핀 변환(선형 변환 + 이동)의 부분 집합.
  - 선들의 평행 상태를 보존함. 투영 평면 방향의 축(예: Z축) 값을 0으로 만들어 투영.
- **원근 투영 (Perspective Projection)**:
  - 거리에 따라 크기가 달라지게 투영평면에 투사. 행렬의 가장 아래 행이 `0 0 0 1`이 아닌 예외적인 형태를 가짐.
  - 3D 투영 변환 후 차원 축소(나눗셈, division by $w$) 과정을 거쳐 구현됨. (예: $y' = -d \frac{y}{z}, x' = -d \frac{x}{z}$)

## 6. 복합 변환
- **특정 점 기준 회전**: 점을 원점으로 이동(Translation) $\rightarrow$ 회전(Rotation) $\rightarrow$ 원래 위치로 되돌림(Translation).
- **임의의 축 기준 회전**: 해당 축이 X축(또는 특정 축)과 일치하도록 공간 변환 $\rightarrow$ 회전 $\rightarrow$ 원래 공간으로 역변환.
- **특정 방향 크기 변환**: 직교 기저(Orthonormal basis) $F$를 구한 후 $X = F \cdot S \cdot F^T$ 형태로 연산.

## 7. 카메라 방향 설정 (Orienting the Camera)
- 카메라 위치 $\vec{c}$, 바라보는 타겟 $\vec{l}$, 카메라의 Up 방향 $\vec{u}'$
- **기저 벡터(Basis Vectors) 계산**:
  1. $\vec{v} = (\vec{c} - \vec{l}) / \|\vec{c} - \vec{l}\|$
  2. $\vec{r} = -(\vec{v} \times \vec{u}') / \|\vec{v} \times \vec{u}'\|$
  3. $\vec{u} = \vec{v} \times \vec{r}$
- 카메라를 원점으로 이동시킨 뒤, 카메라의 기저 벡터들이 월드 좌표계의 축과 일치하도록 행렬을 구성하여 변환을 수행함.
