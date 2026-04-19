# Java Collection Framework (JCF)

## JCF 개요
- 다수의 데이터를 쉽고 효과적으로 처리(추가, 수정, 삭제, 검색, 정렬 등)할 수 있도록 제공하는 자바의 클래스와 인터페이스 집합.
- 동적 자료 관리 가능 (크기가 가변적).

## 주요 인터페이스 구조
- **Collection 인터페이스 하위**:
  - **List**: 순서를 보장하며, 중복된 데이터를 허용 (예: `ArrayList`, `LinkedList`, `Vector`).
  - **Set**: 순서를 보장하지 않으며, 중복된 데이터를 허용하지 않음 (예: `HashSet`, `LinkedHashSet`, `TreeSet`).
  - **Queue**: 선입선출(FIFO) 방식의 데이터 구조.
- **Map**: Key와 Value의 쌍으로 이루어진 구조. Key는 중복 불가능, Value는 중복 가능 (예: `HashMap`, `HashTable`, `TreeMap`).

## Collection Interface의 주요 메서드
- `add(E e)` / `addAll(Collection)`: 데이터 추가.
- `remove(Object)` / `removeAll(Collection)`: 데이터 삭제.
- `size()`: 요소 개수 반환.
- `clear()`: 모든 요소 삭제.
- `contains(Object)`: 특정 요소 포함 여부 확인.
- `isEmpty()`: 컬렉션이 비어있는지 확인.
- `iterator()`: 요소를 순회하기 위한 Iterator 객체 반환.

## ArrayList 클래스
- List 인터페이스의 구현체로, 순서대로 저장되며 중복이 허용되는 동적 배열.
- **주요 함수**:
  - `add(E e)`
  - `get(int index)`: 특정 인덱스의 값을 가져옴.
  - `remove(Object element)`
  - `size()`, `clear()`, `contains()` 등.

## 실습 예제 방향
- `Student` 클래스를 정의 (번호, 이름, 나이, `toString()` 오버라이딩).
- `ArrayList<Student>`를 생성하여 학생 정보를 추가, 리스트 출력, 객체 삭제 후 다시 리스트를 출력해보는 연습 수행.
