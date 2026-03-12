# Health Gamification

Health Gamification is a compact C++ console application that applies simple gamification to everyday fitness activities. The program lets users create profiles, perform Cardio/Strength/Flexibility exercises, complete predefined workouts, earn badges, and appear on a local leaderboard. The codebase is dependency‑free and targets C++17.

## Quick start

1. Open a terminal in the project root.
2. Build with g++ (Windows PowerShell example):

```powershell
g++ -g main.cpp src/*.cpp -I include -o healthgame.exe
```

3. Run the program:

```powershell
.\healthgame.exe
```

## What the app does

On first run the app creates `data/users` (if missing). You can create or log in to a user account, perform exercises or a predefined workout, and earn points and badges. Use the menu to view your profile, check the leaderboard, save progress, logout, or exit. User profiles and the leaderboard are persisted under the `data/` folder in plain text.

## Project layout

- `main.cpp` — application entry and console UI
- `include/` — public headers for each module
- `src/` — implementation files
- `data/` — runtime persisted data (`users/`, `leaderboard.txt`)

## Data & persistence

User profiles are stored as human‑readable text files in `data/users/` and contain the username, points, badges, and recent activities. The leaderboard is stored in `data/leaderboard.txt` and lists users with points and badge counts. These simple formats make it easy to inspect or recover data manually.

## Development notes

- The project uses C++17 features such as `std::filesystem`.
- Exercises are implemented as small classes derived from a common `Exercise` interface; `Workout` aggregates exercises and sums points.
- Badges are defined in code and awarded when users meet thresholds or specific activity triggers.

If you prefer editable badge definitions, I can convert them to a simple text or JSON file and add a loader.

## Troubleshooting

- If compilation fails, ensure your compiler supports C++17 and `-I include` points to the header folder.
- If a saved user or leaderboard file is malformed, delete it to let the app recreate defaults (safe for testing).

## Contributing

Small, focused contributions are welcome. For changes that affect persistence or behavior, include a short manual test or unit test showing the change.

## License

No license file is included. Add a `LICENSE` file (e.g., MIT) if you wish to make reuse terms explicit.

---

## Project purpose and goals

Health Gamification was built as an instructional and prototype application to demonstrate how lightweight gamification mechanics can be applied to encourage healthy behaviours. The goals are to keep the codebase small and approachable, preserve separation of concerns (UI vs domain logic vs persistence), and provide a runnable demo that instructors, students or hobbyists can extend quickly.

## High-level architecture

The application is organized into a clear layered structure: the top-level `main.cpp` drives the console UI and session management; domain modules implement users, exercises, workouts and badges; persistence modules manage reading/writing simple text files for user profiles and the leaderboard. This separation makes it easy to replace or extend persistence (for example, replacing text files with JSON or a small SQLite database) without rewriting business logic.

## Module descriptions (detailed)

`main.cpp` — The entry point provides the console-driven interaction model. On startup it ensures the `data/` directory exists and loads the leaderboard. The program offers a login/create user menu and then a per-user menu. Each menu action creates the appropriate exercise or workout objects, invokes their `perform()` methods (which produce points), updates the `User` object, triggers badge evaluation, and persists state on demand. The main loop is synchronous and intentionally simple for demo purposes.

`User` (include/User.h, src/User.cpp) — Models profile state: `name`, `points`, `earnedBadges`, and a short `activities` log. Key operations are `addPoints`, `addActivity`, `saveToFile`, and `loadFromFile`. The `checkForNewBadges` method iterates all known badges and awards those whose conditions are satisfied. Users are persisted to `data/users/<username>.txt` in a human‑readable format (NAME, POINTS, BADGES, ACTIVITIES).

`Exercise` base + concrete types — `Exercise` defines the interface (virtual `perform()` and `getPoints()`). `CardioExercise`, `StrengthExercise` and `FlexibilityExercise` implement domain-specific parameters and deterministic scoring formulas. `CardioExercise` uses duration and intensity (and computes a simple calorie estimate); `StrengthExercise` maps sets/reps/weight to a volume-style points metric; `FlexibilityExercise` awards sustained-duration points. All scoring operations are constant-time arithmetic.

`Workout` — Aggregates multiple `Exercise*` and executes them in sequence. It returns the sum of points from each exercise. The current design accepts pointers to locally-constructed exercises in `main` and performs workouts immediately; for longer-lived playlists, convert to owning smart pointers.

`Badge` — Small value object that carries `title`, `description`, and `requiredPoints` with an optional `requiredActivity` trigger. The `canEarn` function checks if a user meets the points threshold and/or has performed an activity containing the trigger string.

`FileManager` and `Leaderboard` — Responsible for file-system operations. `FileManager` lists available user files and would be a natural place to add badge-loading logic from external files (if you choose to externalize badge definitions). `Leaderboard` maintains an in-memory vector of entries (username, points, badgeCount), supports loading/saving to `data/leaderboard.txt`, and displays sorted standings.

Data formats (examples)

Example user file `data/users/alice.txt` (simplified):

```
NAME:alice
POINTS:42
BADGES:Getting Started,Hydration Champion
ACTIVITIES:
Cardio: Morning Run
Flexibility: Morning Yoga
```

Example leaderboard `data/leaderboard.txt` (space-separated per line):

```
alice 42 2
bob 100 3
```

Design decisions and algorithms

Most operations are intentionally lightweight. Badge evaluation iterates the small badge list and runs a substring search across the user's activity log for activity-triggered badges; this is linear and cheap given short logs. Leaderboard updates upsert the user's row and sort the vector before saving — sorting cost is O(N log N) for N users, which is acceptable for small to medium user counts.

Testing and recommended checks

Manual test scenarios: create a user, perform each exercise type, verify points and badge awarding, save and reload the user to confirm persistence, and update the leaderboard. For automated testing, write unit tests for points computation, badge rules, and persistence round-trips. Adding a simple test harness (GoogleTest) and a minimal CI workflow is recommended once you adopt JSON or a more structured persistence format.

Suggested next features

- Externalize badges to a JSON or CSV file and load them at startup. This enables non-developer editing of criteria.
- Improve input handling in `main` to avoid `cin` failure modes (use `getline` and parse integers robustly).
- Replace raw pointers in `Workout` with `unique_ptr` for clearer ownership.
- Add atomic file writes (write to temp file and rename) to avoid corruption during writes.

Troubleshooting

If the build fails, verify your compiler supports C++17 and that the `include/` directory is accessible using `-I include`. If user or leaderboard files are corrupted, remove them to allow the app to recreate defaults. If non-ASCII characters display oddly in PowerShell, set the console encoding to UTF-8 or remove special characters from strings.

How I can help next

I can produce a `run_demo.ps1` script that builds and runs a scripted demo, generate slide-ready one-paragraph descriptions for each module, or implement external badge loading and safer persistence. Tell me which you prefer and I will implement it.

