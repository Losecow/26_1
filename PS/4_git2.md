# Git 이력 관리 및 원격 저장소, 브랜치

## 커밋 이력 수정 및 취소
- **`git commit --amend`**: 최근 커밋을 수정 (메시지 변경 또는 누락된 파일 추가).
- **`git reset`**: 특정 커밋으로 되돌아가며, 이후의 커밋 히스토리를 삭제.
  - `--soft`: HEAD만 이동하고 Working Directory 보존, 파일은 Staging Area에 남음.
  - `--mixed` (기본값): HEAD 이동, Working Directory 보존, 파일은 Unstaged 상태로 남음.
  - `--hard`: HEAD 이동, Working Directory 내용도 변경 전으로 삭제.
- **`git revert`**: 기존 커밋 내역을 삭제하지 않고, 되돌리려는 커밋의 취소 작업을 새로운 커밋으로 추가.

## Remote Repository (원격 저장소) 작업
- **`git clone`**: 원격 저장소 복제.
- **`git remote`**: 원격 저장소 연결 관리 (`add`, `remove`, `-v`).
- **`git push`**: 로컬 저장소의 변경 내역을 원격 저장소로 전송.
- **`git fetch`**: 원격 저장소의 변경 내역을 가져오기만 함 (병합 안 함).
- **`git pull`**: 원격 저장소의 내역을 가져와 현재 브랜치에 병합 (`fetch` + `merge`).

## Branch (브랜치) 관리
- 독립적인 작업 공간을 제공 (기본 브랜치: `master` 또는 `main`).
- **생성 및 확인**:
  - `git branch <name>`: 생성.
  - `git branch -a`: 모든 브랜치 확인.
  - `git branch -d <name>`: 삭제.
- **이동 (Checkout)**:
  - `git checkout <name>`: 해당 브랜치로 이동.
  - `git checkout -b <name>`: 브랜치 생성 후 즉시 이동.
- **병합 (Merge)**:
  - `git merge <name>`: 지정한 브랜치의 내용을 현재 브랜치로 병합.

## Branch 전략
- **Git Flow**: `master`, `develop`, `feature`, `release`, `hotfix` 등 명확하게 나뉜 구조적 협업 전략.
- **GitHub Flow**: `master(main)`와 `feature` 브랜치만을 사용하는 단순하고 빠른 배포 전략.
