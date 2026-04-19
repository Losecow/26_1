# Git 고급 기능 (Stash, 병합 전략, Rebase 등)

## Git Stash
- Working Directory에서 수정한 파일(Modified, Staged)을 임시로 보관하는 장소.
- 커밋하지 않고 다른 브랜치로 이동해야 할 때 유용.
- 명령어:
  - `git stash`: 임시 저장.
  - `git stash list`: 저장된 목록 확인.
  - `git stash apply`: 임시 저장한 내용 적용.
  - `git stash pop`: 적용과 동시에 목록에서 삭제.
  - `git stash drop / clear`: 삭제.

## Git Merge 전략
- **Fast-forward (`--ff`)**: 병합할 브랜치가 현재 브랜치의 이후 커밋일 경우, 별도의 병합 커밋 없이 HEAD만 이동.
- **No Fast-forward (`--no-ff`)**: 병합 커밋(Merge commit)을 강제로 생성하여 병합 기록을 남김.
- **Squash (`--squash`)**: 병합할 브랜치의 여러 커밋을 하나로 묶어 Staging Area에 올린 상태로 병합 (병합 커밋이 자동으로 생성되지 않아 수동 커밋 필요).

## Merge Conflict (병합 충돌)
- 두 브랜치에서 같은 파일의 동일한 부분을 수정한 후 병합할 때 발생.
- `<<<<<<< HEAD`, `=======`, `>>>>>>> branch_name` 형태로 충돌 부분이 파일에 표시됨.
- 개발자가 직접 코드를 수정하여 충돌을 해결한 후 `git add` 및 `git commit`을 진행해야 함.

## 기타 고급 명령어
- **`git cherry-pick <commit>`**: 다른 브랜치의 특정 커밋만 선택하여 현재 브랜치에 적용.
- **`git reflog`**: 브랜치 이동 등 HEAD의 모든 참조 기록을 확인하여 실수로 지운 커밋 등을 복구할 때 사용.
- **`git rebase`**: 브랜치의 Base를 다른 브랜치(예: master)의 최신 커밋으로 재설정하여 커밋 히스토리를 깔끔하게(선형으로) 만듦.
- **`git rebase -i`**: 대화형(Interactive) Rebase로, 커밋 메시지 변경(reword), 커밋 합치기(squash), 삭제(drop) 등 커밋 히스토리를 세밀하게 편집 가능.
