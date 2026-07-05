# Netflix Inventory Management System - StreamIt

A CLI-based Netflix-style content rental system built in C++ with OOPS principles.

## Features

**User Account:**
- Sign-up with unique username
- Login with credentials
- Browse movies and TV shows
- View content details

**Admin Account:**
- Add movies and TV shows to inventory
- View all content
- Manage system data

**Content Types:**

Movies:
- Title, Genre, Rating
- Duration, Rent Cost, Purchase Cost

TV Shows:
- Title, Genre, Rating
- Seasons, Episodes per Season
- Per Season Rent Cost, Per Season Purchase Cost

## Getting Started

### Run with Docker

```bash
docker build -t streamit .
docker run -it streamit
```

### Compile & Run Locally

```bash
g++ start.cpp -o app
./app
```

## Default Credentials

- **Admin:** username: `admin` | password: `admin`

## File Structure

- `start.cpp` - Main application source code
- `content.txt` - Persistent content storage
- `users.txt` - Persistent user accounts storage
- `Dockerfile` - Docker configuration
