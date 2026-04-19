# 객체지향 프로그래밍 (OOP) 실습

## 객체지향 프로그래밍 기초
- **특징**: 절차지향과 대비되며, 유지보수 용이, 재사용성 증가, 현실 세계 모델링.
- **OOP의 4대 핵심 개념**:
  - **캡슐화 (Encapsulation)**: 데이터와 메서드를 하나로 묶고 접근제어자(`public`, `private`, `protected`, `default`)로 은닉.
  - **상속 (Inheritance)**: 기존 클래스를 재사용하여 새로운 클래스를 작성.
  - **다형성 (Polymorphism)**: 오버로딩(Overloading), 오버라이딩(Overriding).
  - **추상화 (Abstraction)**: 공통적인 특징을 추출하여 추상 클래스나 인터페이스로 정의.

## Class와 Object
- **Class (클래스)**: 객체를 생성하기 위한 설계도(템플릿). 속성(변수)과 동작(메서드), 생성자로 구성.
- **Object (객체)**: 클래스를 기반으로 메모리에 생성된 실체 (인스턴스).

## 배열 (Array)
- **기본 타입 배열**: `int[] scores = new int[4];` 처럼 기본 자료형 데이터를 순차적으로 저장.
- **객체 타입 배열**: 클래스 타입의 객체들을 저장하는 배열.
  ```java
  Person[] people = new Person[3];
  people[0] = new Person("Alice", 25);
  for (Person p : people) {
      p.introduce();
  }
  ```

## 실습 예제: BmiCalculator
- **클래스 정의**: 키, 몸무게 변수 및 BMI 계산 메서드 포함.
- **객체 배열 활용**: 입력받은 인원수 만큼 `BmiCalculator` 객체 배열을 생성하여, 각 객체의 메서드를 호출하고 조건(BMI > 25)에 맞는 결과를 산출.
