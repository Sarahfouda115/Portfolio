const Skills = () => {
  const skillCategories = [
    {
      title: "Programming",
      skills: [
        { name: "Python", level: 90 },
        { name: "C++", level: 80 },
        { name: "SQL", level: 75 }
      ]
    },
    {
      title: "Data Analysis",
      skills: [
        { name: "Pandas", level: 85 },
        { name: "NumPy", level: 85 },
        { name: "Matplotlib", level: 80 }
      ]
    },
    {
      title: "Tools & Platforms",
      skills: [
        { name: "Power BI", level: 85 },
        { name: "Excel", level: 90 },
        { name: "Git", level: 70 }
      ]
    }
  ];

  const otherSkills = [
    "Problem Solving",
    "Mathematics",
    "Team Collaboration",
    "Data Structures",
    "OOP",
    "Algorithms"
  ];

  const languages = [
    { name: "Arabic", level: "Native" },
    { name: "English", level: "Professional Proficiency" }
  ];

  return (
    <section id="skills" className="py-24 px-6 bg-muted/30 relative">
      {/* Background accent */}
      <div className="absolute right-0 top-1/2 -translate-y-1/2 w-96 h-96 bg-primary/5 rounded-full blur-3xl" />

      <div className="max-w-6xl mx-auto relative z-10">
        {/* Section header */}
        <div className="text-center mb-16">
          <span className="text-primary text-sm font-display uppercase tracking-widest mb-4 block">
            Expertise
          </span>
          <h2 className="font-display text-4xl md:text-5xl font-bold">
            Technical{" "}
            <span className="gradient-text">Skills</span>
          </h2>
        </div>

        {/* Skills grid */}
        <div className="grid md:grid-cols-3 gap-8 mb-16">
          {skillCategories.map((category) => (
            <div
              key={category.title}
              className="gradient-card rounded-2xl border border-border p-6"
            >
              <h3 className="font-display text-lg font-semibold mb-6 text-primary">
                {category.title}
              </h3>
              <div className="space-y-5">
                {category.skills.map((skill) => (
                  <div key={skill.name}>
                    <div className="flex justify-between mb-2">
                      <span className="text-sm font-medium">{skill.name}</span>
                      <span className="text-sm text-muted-foreground">{skill.level}%</span>
                    </div>
                    <div className="h-2 bg-secondary rounded-full overflow-hidden">
                      <div
                        className="h-full gradient-primary rounded-full transition-all duration-1000 ease-out"
                        style={{ width: `${skill.level}%` }}
                      />
                    </div>
                  </div>
                ))}
              </div>
            </div>
          ))}
        </div>

        {/* Other skills & Languages */}
        <div className="grid md:grid-cols-2 gap-8">
          {/* Other skills */}
          <div className="gradient-card rounded-2xl border border-border p-6">
            <h3 className="font-display text-lg font-semibold mb-6">Other Skills</h3>
            <div className="flex flex-wrap gap-3">
              {otherSkills.map((skill) => (
                <span
                  key={skill}
                  className="px-4 py-2 rounded-full bg-secondary text-secondary-foreground text-sm hover:bg-primary/20 hover:text-primary transition-colors cursor-default"
                >
                  {skill}
                </span>
              ))}
            </div>
          </div>

          {/* Languages */}
          <div className="gradient-card rounded-2xl border border-border p-6">
            <h3 className="font-display text-lg font-semibold mb-6">Languages</h3>
            <div className="space-y-4">
              {languages.map((lang) => (
                <div key={lang.name} className="flex items-center justify-between">
                  <span className="font-medium">{lang.name}</span>
                  <span className="px-4 py-1.5 rounded-full bg-primary/10 text-primary text-sm">
                    {lang.level}
                  </span>
                </div>
              ))}
            </div>
          </div>
        </div>
      </div>
    </section>
  );
};

export default Skills;
