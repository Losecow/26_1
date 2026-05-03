# Database Systems - SQL DDL & E-R Model 요약

## 1. SQL DDL (데이터 정의어)

### 데이터 타입 (Data Types)
- **문자열 (String)**:
  - `CHAR(n)`: 고정 길이 문자열 (최대 255바이트). 길이가 항상 같을 때 사용.
  - `VARCHAR(n)`: 가변 길이 문자열 (최대 65,535바이트). 길이가 변할 때 사용.
  - `TEXT`: `VARCHAR` 범위를 초과하는 아주 긴 문자열 (`TINYTEXT`, `TEXT`, `MEDIUMTEXT`, `LONGTEXT`).
- **숫자형 (Numeric)**:
  - **정수형**: `TINYINT`, `SMALLINT`, `MEDIUMINT`, `INT`/`INTEGER`, `BIGINT`
  - **고정 소수점**: `NUMERIC(p,d)` / `DECIMAL(p,d)` (정확한 값 저장, 예: 금액).
  - **부동 소수점**: `FLOAT`, `DOUBLE`, `REAL` (근사값, 속도는 빠르나 오차가 있을 수 있음).
- **날짜 및 시간 (Temporal)**:
  - `DATE` (YYYY-MM-DD), `TIME` (HH:MM:SS), `DATETIME` (YYYY-MM-DD HH:MM:SS), `YEAR`
  - `TIMESTAMP(n)`: Unix time (1970-01-01 이후의 시간 기록, 주로 로깅에 사용).
- **대형 객체 (Large Objects)**:
  - `BINARY(n)`, `VARBINARY(n)`: 이진 바이트 문자열.
  - `BLOB` (Binary Large Object, `TINYBLOB`, `BLOB`, `MEDIUMBLOB`, `LONGBLOB`).

### 무결성 제약 조건 (Integrity Constraints)
- `PRIMARY KEY`: 각 행을 고유하게 식별. `NULL` 허용 안 됨. 테이블당 1개만 존재.
- `UNIQUE`: 속성 값이 튜플(행) 간에 고유함을 보장. `NULL` 허용 가능. 여러 개 지정 가능.
- `FOREIGN KEY`: 다른 테이블의 `PRIMARY KEY`를 참조하여 참조 무결성(일관성)을 유지.
- `NOT NULL`: 데이터가 비어있는(`NULL`) 상태를 방지.
- `DEFAULT`: 값이 삽입되지 않았을 때 들어갈 기본값을 설정.
- `CHECK`: 삽입되는 값이 특정 조건을 만족하는지 검사 (예: `budget > 50000`).

### CREATE TABLE 명령어
새로운 릴레이션(테이블)을 정의할 때 사용. 각 속성(컬럼)의 이름, 데이터 타입, 제약 조건을 지정함.

---

## 2. 데이터베이스 설계 (Database Design)

### 설계 단계 (Design Phases)
1. **초기 단계 (Problem analysis)**: 데이터 요구사항 파악 및 분석
2. **데이터 모델 선택 (Choosing a data model)**: 요구사항을 개념적 스키마로 변환
3. **설계 (Design)**:
   - **논리적 설계 (Logical Design)**: 데이터베이스 스키마(관계 스키마) 결정 (어떤 속성을 어느 테이블에 둘 것인가).
   - **물리적 설계 (Physical Design)**: 데이터베이스의 물리적 레이아웃 결정.
- **주요 고려사항**: 
  - 중복성(Redundancy) 회피: 데이터 불일치 유발 방지.
  - 불완전성(Incompleteness) 회피: 필요한 데이터 모델링이 불가능해지는 것 방지.

---

## 3. E-R 모델 (Entity-Relationship Model)

데이터베이스의 전체 논리적 구조를 그래픽으로 표현하는 다이어그램 모델 (E-R Diagram).

### 기본 개념
- **엔티티 (Entity)**: 구별 가능한 객체 (예: 특정 학생, 회사). 사각형으로 표시.
  - **엔티티 집합 (Entity Set)**: 동일한 속성을 공유하는 엔티티들의 모임.
- **관계 (Relationship)**: 여러 엔티티 간의 연관성. 다이아몬드로 표시.
  - **관계 집합 (Relationship Set)**: 관계들의 수학적 집합 (보통 2진 관계, 드물게 3진 관계도 존재). 관계도 자신만의 속성을 가질 수 있음.
- **속성 (Attribute)**: 엔티티를 설명하는 특징.
  - **종류**: 단순/복합(Composite, 더 작은 부분으로 나뉨), 단일값/다중값(Multivalued), 파생(Derived, 다른 속성에서 계산됨) 속성.

### 매핑 카디널리티 (Mapping Cardinalities)
관계 집합을 통해 다른 엔티티와 연관될 수 있는 엔티티의 수:
- **1:1 (One-to-one)**: 화살표(`→`)로 양방향 표시. 양쪽 모두 최대 1개와 연관.
- **1:N (One-to-many)**: 한 쪽(1)이 여러 개와 연관, 반대쪽(N)은 1개와 연관.
- **N:1 (Many-to-one)**: 여러 개가 1개와 연관.
- **N:M (Many-to-many)**: 직선(`—`)으로 양방향 표시. 양쪽 모두 여러 개와 연관.
- **참여도 (Participation)**:
  - **전체 참여 (Total)**: 두 줄(`=`)로 표시. 엔티티 집합의 모든 엔티티가 관계에 반드시 1번 이상 참여해야 함.
  - **부분 참여 (Partial)**: 한 줄(`-`)로 표시. 일부 엔티티는 관계에 참여하지 않을 수 있음.
- **최소/최대 카디널리티 (`l..h`)**: 예) `1..1` (반드시 1개), `0..*` (0개 이상 무제한).

### 기본 키 (Primary Key) 지정 방법
- **강한 엔티티 집합**: 엔티티를 고유하게 식별할 수 있는 속성(들).
- **관계 집합**: 참여하는 엔티티들의 기본 키 합집합 + 관계의 자체 속성. (N:M은 양쪽 키 합집합, 1:N/N:1은 'N'쪽 엔티티의 키, 1:1은 둘 중 하나의 키 사용).
- **약한 엔티티 집합 (Weak Entity Set)**:
  - 다른 식별 엔티티(강한 엔티티)에 존재가 종속되어, 자체적인 기본 키가 없는 엔티티 집합.
  - 이중 사각형으로 표시하며, 식별 관계는 이중 다이아몬드로 표시.
  - 고유한 구별을 위해 **부분 키(Discriminator)** 를 사용하며, 점선 밑줄로 표시.
  - **기본 키** = 식별 엔티티(부모)의 기본 키 + 자신의 부분 키(Discriminator).