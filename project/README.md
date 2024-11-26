# IdeaSea - a website where uniqueness, randomness, and creativity can shine
#### Video Demo: https://www.youtube.com/watch?v=gI_UIBOPgMg

#### Description:
As my final project of CS50x, I initially wanted to create a Strava-linked journal with a built-in TODO list using the Strava API. The idea was inspired by my physical real-life journal and TODO list where I also keep track of my physical activities. However, I realized that this idea might not be the most creative one, as there are already plenty of TODO lists, journals, and Strava itself. I felt like the creativity was lacking, and that's when I realized that what I was truly looking for was creativity itself. That's why I decided to go with the idea of IdeaSea.

IdeaSea is meant to be a vintage, old-school-looking website where users can post ideas. It is not a simple post wall or a thematically designed forum; it’s a site designed to inspire others with creative ideas. From the most absurd ideas, like challenges such as crossing a country in a completely straight line, to simpler ones, like a weird, perhaps never-before-seen recipe idea, IdeaSea aims to provoke creative thinking. Why limit yourself? Of course, some ideas might be dangerous and need more thorough research, but that's the entire point of the site! It’s about sparking thought, encouraging people to come up with ideas, and using their heads instead of mindlessly scrolling through most social media apps these days.

I’ve always thought of myself as someone who’s not very creative, although people around me often said otherwise. I struggled to inspire myself to come up with ideas that I found interesting and valuable. At some point, I realized that many others might struggle with inspiration too. That’s why I believe there’s a need for places like this—places where only ideas and inspiration can shine, rather than pointlessness and time-wasting.

The site is designed to function like a post wall where users can post both anonymously and under their usernames. I’ve decided to require people to sign up for an account in order to post (even anonymously), though anyone can browse the site without an account. This ensures some moderation, so that posts remain relevant to ideas and inspiration. In the future, I plan to extend the site by building a mobile app, making it easier for people to draw inspiration from a simple click, even when they’re in bed, without needing to browse websites or turn on their PCs.

I also plan to add more features, such as random idea generators or music-related content like a random playlist generator to inspire people to explore ideas through music.

I chose a vintage-synthwave style for the site to make it stand out, giving it a unique aesthetic that's less minimalistic than what’s typical today, while still capturing that "abstract vibe." In the future, I hope to renovate the site to make it cleaner and more polished.

### Files:
- **Static folder**: Contains free-to-use fonts to make the site look more interesting, along with the CSS file.
- **Templates folder**:
  - `layout.html`: Contains the layout for the site used on every page, utilizing Jinja.
  - `index.html`: Displays the main page with all posts from users, generated from the database.
  - `ideasea.db`: The database storing all posts, users, their passwords, nicknames, and post counts.
  - `login.html` and `register.html`: Pages for user login and registration.
  - `apology.html`: Displays meme-like apologies, inspired by CS50’s Finance problem.
  - `about.html`: Contains virtual sticky notes with information about the site’s concept and mission.
  - `create.html`: Allows users to write and submit posts to the wall.
  - `account.html`: Lets users change their usernames and passwords.
  - `contact.html`: A sticky note with my email for contacting the website's author.
  - `post_detailed.html`: A dynamically generated page for viewing a full post when clicked.
  - `app.py`: The backend, containing all necessary functions, requests, redirects, renders, database access, and website logic.

**Note**: After submitting the site, I plan to host it on a domain and continue improving it. My goal is to get into data science after CS50x, and I’m looking forward to creating a "categories.html" file or something similar, which would use machine learning to categorize posts automatically. This way, users won't have to specify a category for their posts—an ML model will analyze keywords and assign a category.
