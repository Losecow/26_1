# Make Utility 및 Makefile

## Make Utility
- 소프트웨어 개발을 위해 유닉스 계열 운영 체제에서 주로 사용되는 프로그램 빌드 도구.
- 여러 파일들의 의존성과 필요한 명령을 정의하여 반복적 명령을 자동화.
- 장점: 시간 절약, 프로그램의 종속 구조 파악 용이, 반복 작업 최소화.

## Makefile 구조
Makefile은 다음과 같은 구조로 작성됩니다:
```makefile
Target : Dependency1 Dependency2 ...
<tab>Command1
<tab>Command2
```
- **Target**: 명령어가 수행된 후 생성될 결과 파일명.
- **Dependency**: 대상 파일을 생성하기 위해 필요한 파일들 (파일 수정 날짜를 체크하여 필요 시에만 빌드).
- **Command**: 실행할 명령어 (반드시 Tab으로 들여쓰기 해야 함).

## Macro (매크로)
- 문자열을 간단하게 표현하기 위해 변수를 정의하여 사용.
- `NAME = 문자열` (관습적으로 대문자 사용).
- `$(NAME)` 형태로 참조.

## Suffix Rule (확장자 규칙)
- 파일 확장자를 보고 적절한 명령을 실행하는 규칙 (예: `.c`를 컴파일하여 `.o` 생성).

## Automatic Variable (자동 변수)
- `$@`: 현재 Target의 이름.
- `$^`: Dependency 전체 목록.
- `$*`: 확장자가 없는 현재 Target 이름.
- `$<`: 첫 번째 Dependency의 이름.
- `$?`: Dependency 중 현재 Target보다 최근에 갱신된 파일들.
