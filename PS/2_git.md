# Git 기초 및 버전 관리 시스템 (VCS)

## VCS (Version Control System)
- **목적**: 프로젝트 개발 시 소스코드, 문서 등의 버전을 관리.
- **종류**:
  - **CVCS (Centralized VCS)**: 중앙집중식, 서버에 소스와 히스토리 저장 (예: CVS, SVN). 서버 장애 시 협업 어려움.
  - **DVCS (Distributed VCS)**: 분산 관리 시스템, 여러 PC에 분산 저장 (예: Git, Mercurial). 중앙 서버와 독립적으로 로컬에서 완벽하게 소스와 이력 관리 가능.

## Git과 GitHub
- **Git**: 로컬 저장소(Local Repository)를 사용하여 분산 버전 관리를 수행하는 소프트웨어.
- **GitHub**: Git을 기반으로 원격 저장소(Remote Repository)를 제공하고 협업을 지원하는 웹 서비스.

## Git 연동 및 설정
- **지원**: Windows, Mac, Linux 등.
- **설정 명령어**:
  ```bash
  git config --global user.name "username"
  git config --global user.email "user@email.com"
  git config --global color.ui auto
  git config --global --list
  ```

## Git 버전 관리 과정
1. **Working Directory**: 현재 작업 중인 폴더.
2. **Staging Area**: `git add`를 통해 커밋될 준비가 된 파일들이 있는 영역.
3. **Git Repository (Local)**: `git commit`을 통해 파일들의 버전 기록이 저장된 영역.

## 주요 명령어
- **초기화 및 복제**:
  - `git init`: 로컬 저장소 생성.
  - `git clone <URL>`: 원격 저장소 복제.
- **파일 추가 및 커밋**:
  - `git add <file>`: 변경사항을 Staging Area에 추가.
  - `git commit -m "메시지"`: Staging Area의 내용을 로컬 저장소에 커밋.
  - `git commit -am "메시지"`: Tracked 파일의 경우 add와 commit을 동시에 수행.
- **삭제**:
  - `git rm <file>`: 로컬 디렉터리와 Git 저장소에서 모두 삭제.
  - `git rm --cached <file>`: 로컬 디렉터리 파일은 유지하고 Git 저장소(Staging Area)에서만 삭제.
- **상태 확인 및 비교**:
  - `git status`: 현재 파일의 상태 (Untracked, Staged 등) 확인.
  - `git diff`: 변경된 내용 비교 (Working Directory와 Staging Area, 혹은 커밋 간 비교).
- **기록 확인**:
  - `git log`: 커밋 히스토리 확인. `git log --oneline --graph` 등의 옵션 활용 가능.

## .gitignore
- Git 저장소에서 관리할 필요가 없는 파일이나 폴더(실행 파일, 숨김 파일, 보안 정보 등)를 명시하여 버전 관리에서 제외시키는 파일.
