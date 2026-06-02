#!/usr/bin/env bash
set -euo pipefail

# Project worktree helper — fits any repo
REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
FEATURE="${1:-$(whoami)-$(date +%s)}"
BRANCH="feat/${FEATURE}"
WTDIR="${REPO_ROOT}/.claude/worktrees/${FEATURE}"

if [ -d "$WTDIR" ]; then
    echo "Worktree already exists at $WTDIR"
    exit 1
fi

git -C "$REPO_ROOT" worktree add "$WTDIR" -b "$BRANCH"
echo "$WTDIR"
