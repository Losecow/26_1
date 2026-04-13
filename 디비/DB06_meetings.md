# ECE30030/ITP30010 Database Systems - 06: SQL DDL & E-R Model

## 1. SQL DDL (Data Definition Language)

### 데이터 타입 (Domain Types in SQL)
*   **문자열 데이터 타입 (String Data Types)**
    *   `CHAR(n)`: 고정 길이 문자열 (최대 255)
    *   `VARCHAR(n)`: 가변 길이 문자열 (최대 65,535). 길이가 고정된 경우 `CHAR`를, 변동이 큰 경우 `VARCHAR`를 사용.
    *   `TEXT`: VARCHAR보다 긴 문자열 (`TINYTEXT`, `TEXT`, `MEDIUMTEXT`, `LONGTEXT`)
*   **숫자 데이터 타입 (Numeric Data Types)**
    *   정수형: `TINYINT`, `SMALLINT`, `MEDIUMINT`, `INT/INTEGER`, `BIGINT`
    *   고정 소수점: `NUMERIC(p,d)` / `DECIMAL` (정확한 값 저장, 합계 연산 등에 유리)
    *   부동 소수점: `FLOAT`, `REAL`, `DOUBLE` (DECIMAL보다 연산이 빠름)
*   **시간 데이터 타입 (Temporal Data Types)**
    *   `DATE`: 'YYYY-MM-DD'
    *   `TIME`: 'HH:MM:SS'
    *   `DATETIME`: 'YYYY-MM-DD HH:MM:SS'
    *   `YEAR`: 'YYYY'
    *   `TIMESTAMP(n)`: Unix time (1970년 1월 1일 기준). 주로 로깅용으로 사용되며 크기 `n`에 따라 표시 형식이 변경됨.
*   **이진/대형 객체 (Large Objects)**
    *   `BINARY(n)`, `VARBINARY(n)`: 바이트(Byte) 문자열
    *   `BLOB`: Binary Large OBject (`TINYBLOB`, `BLOB`, `MEDIUMBLOB`, `LONGBLOB`)

### 무결성 제약 조건 (Integrity Constraints)
`CREATE TABLE` 사용 시 데이터베이스에 의미 있는 데이터만 저장되도록 조건을 설정.
*   **키 제약 조건 (Declaring Keys)**
    *   `PRIMARY KEY`: 각 행을 고유하게 식별. `NULL` 허용 불가, 테이블당 1개만 존재 (Clustered index).
    *   `UNIQUE`: 속성 값의 고유성을 보장. `NULL` 허용 가능, 테이블당 여러 개 존재 가능 (Non-clustered index).
    *   `FOREIGN KEY`: 다른 릴레이션의 Primary Key를 참조하여 참조 무결성(Referential integrity)을 유지.
*   **기타 제약 조건**
    *   `NOT NULL`: `NULL` 값(데이터가 알려지지 않음) 입력을 방지.
    *   `DEFAULT`: 입력값이 없을 때 삽입될 기본값 설정 (예: `DEFAULT CURRENT_TIMESTAMP`).
    *   `CHECK`: 입력값이 특정 조건을 만족하는지 확인 (예: `CHECK (budget > 50000)`).

---

## 2. 데이터베이스 설계 (Database Design)

### 설계 단계 (Design Phases)
1.  **요구사항 분석 (Problem Analysis)**: 데이터 요구사항 파악.
2.  **데이터 모델 선택 (Choosing a Data Model)**: 요구사항을 개념적 스키마(Conceptual Schema)로 변환.
3.  **설계 (Design)**
    *   **논리적 설계 (Logical Design)**: 데이터베이스 스키마 결정 (어떤 속성을 기록하고 어떻게 분배할 것인가).
    *   **물리적 설계 (Physical Design)**: 데이터베이스의 물리적 레이아웃 결정.
*   **주의해야 할 주요 함정 (Pitfalls)**
    *   **중복성 (Redundancy)**: 반복되는 정보는 데이터 불일치를 초래함.
    *   **불완전성 (Incompleteness)**: 특정 정보를 모델링할 수 없게 됨.

### E-R 모델 (Entity-Relationship Model)
기업의 구조를 개체(Entities)와 관계(Relationships)의 집합으로 모델링.

*   **개체 집합 (Entity Sets)**
    *   구별 가능한 객체들의 집합.
    *   **속성 (Attributes)**: 개체를 설명하는 성질.
        *   Simple/Composite(복합 속성 - 하위로 나뉠 수 있음)
        *   Single-valued/Multivalued(다중값 속성 - 중괄호 `{}` 로 표시)
        *   Derived(파생 속성 - 다른 속성으로부터 계산됨)
*   **관계 집합 (Relationship Sets)**
    *   여러 개체 간의 연관성 (주로 2개의 개체를 연결하는 Binary relationship). E-R 다이어그램에서 마름모로 표시됨.
    *   관계 집합 자체도 속성(예: `date`)을 가질 수 있음.

### 대응 수 (Mapping Cardinalities)
한 개체가 관계를 통해 연관될 수 있는 다른 개체의 수를 나타냄.
*   **1:1 (One-to-one)**: 화살표(`->`)로 표시.
*   **1:N (One-to-many)**
*   **N:1 (Many-to-one)**
*   **M:N (Many-to-many)**: 실선(`-`)으로 표시.

### 참여 제약 조건 (Participation Constraints)
*   **전체 참여 (Total Participation)**: 개체 집합의 모든 개체가 하나 이상의 관계에 참여해야 함 (이중선 `=`로 표시).
*   **부분 참여 (Partial Participation)**: 일부 개체는 관계에 참여하지 않을 수 있음.
*   `min..max` 표기법: 예) `1..1` (정확히 1개), `0..*` (0개 이상)

### E-R 모델에서의 Primary Key
*   **개체 집합 (Entity Sets)**: 개체를 식별하기에 충분한 속성들의 집합.
*   **관계 집합 (Relationship Sets)**: 연관된 개체들의 Primary Key의 합집합을 이용함.
    *   `M:N`: 양쪽 PK의 합집합.
    *   `1:N` / `N:1`: 'Many' 쪽의 PK를 사용.
    *   `1:1`: 어느 쪽의 PK든 선택 가능.

### 약한 개체 집합 (Weak Entity Sets)
*   자체적인 Primary Key가 없으며, **식별 개체(Identifying entity = 강한 개체)**의 존재에 의존적임.
*   **구별자 (Discriminator)**: 약한 개체들을 구별하기 위한 속성 세트 (점선 밑줄로 표시).
*   **Primary Key** = 식별 개체의 Primary Key + 구별자(Discriminator).
*   표기법: 약한 개체 집합은 **이중 사각형(Double rectangle)**, 식별 관계는 **이중 마름모(Double diamond)**로 표시.