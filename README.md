# Czas w C++: std::chrono

Laboratorium o mierzeniu i reprezentowaniu czasu w C++ z biblioteką std::chrono: durations, zegary, punkty w czasie, kalendarz i strefy czasowe.

## Struktura

- `lab/` — notebooki JupyterLab z materiałami i ćwiczeniami; zacznij od `lab/_start.ipynb`
  - `lab/cmake/lab.cmake` — wspólne ustawienia CMake (C++20, GoogleTest)
- `pyproject.toml` — środowisko Pythona dla notebooków (zarządzane przez [uv](https://docs.astral.sh/uv/))

## Jak zacząć

```bash
uv sync
uv run --with jupyterlab jupyter lab lab/_start.ipynb
```

Szczegółowa instrukcja instalacji — w przygotowaniu.

## Autorzy

- Tomasz Idźkowski (idzkowskit@student.agh.edu.pl)
- Kacper Kobieluch (kkobieluch@student.agh.edu.pl)
- Maksymilian Koleśniak (mkolesniak@student.agh.edu.pl)
