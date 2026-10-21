# Czas w C++: std::chrono

Laboratorium o mierzeniu i reprezentowaniu czasu w C++ z biblioteką std::chrono: durations, zegary, punkty w czasie, kalendarz i strefy czasowe.

## Struktura

- `lab/` — notebooki JupyterLab z materiałami i ćwiczeniami; zacznij od `lab/_start.ipynb`
  - `lab/cmake/lab.cmake` — wspólne ustawienia CMake (C++20, GoogleTest)
- `pyproject.toml` — środowisko Pythona dla notebooków (zarządzane przez [uv](https://docs.astral.sh/uv/))

## Jak zacząć

### 1. Kompilator C++20 i CMake

Minimalne wersje: GCC 11.2 albo Clang 14, Visual Studio 2022 17.0, CMake 3.22
(szczegóły i uzasadnienie — w `lab/_start.ipynb`).

- **Ubuntu / Debian / WSL** (Ubuntu 22.04 lub nowszy):
  ```bash
  sudo apt install g++ cmake
  ```
- **Windows**: najprościej przez WSL z Ubuntu (jak wyżej). Alternatywnie Visual Studio 2022
  z pakietem *Desktop development with C++* (zawiera CMake); notebooki uruchamiaj
  wtedy z „Developer PowerShell for VS 2022”, żeby `cmake` widział kompilator.
- **macOS**: Xcode Command Line Tools i CMake (np. `brew install cmake`) — konfiguracja niesprawdzana.

Notebook `05_extras` (formatowanie dat, strefy czasowe) wymaga GCC 13+ albo Visual Studio 2022 17.2+;
pozostałe działają na wersjach minimalnych.

### 2. Python i JupyterLab

Środowiskiem Pythona zarządza [uv](https://docs.astral.sh/uv/getting-started/installation/). Po jego instalacji,
w katalogu repozytorium:

```bash
uv sync
uv run --with "jupyterlab>=4" jupyter lab lab/_start.ipynb
```

Pierwsza kompilacja ćwiczenia pobiera GoogleTest (raz, do `lab/_deps`) — potrzebny jest wtedy dostęp do internetu.

## Autorzy

- Tomasz Idźkowski (idzkowskit@student.agh.edu.pl)
- Kacper Kobieluch (kkobieluch@student.agh.edu.pl)
- Maksymilian Koleśniak (mkolesniak@student.agh.edu.pl)
