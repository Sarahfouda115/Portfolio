import { ExternalLink, BarChart2, Users, Cloud } from "lucide-react";
import { Button } from "./ui/button";

const Projects = () => {
  const projects = [
    {
      icon: BarChart2,
      title: "Retail Analytics Dashboard",
      description: "Built end-to-end sales analysis system identifying seasonal trends and product performance.",
      technologies: ["Python", "Pandas", "Matplotlib", "Power BI", "Excel"],
      color: "from-primary to-cyan-400"
    },
    {
      icon: Users,
      title: "Student Management System",
      description: "Developed C++ application managing student records with file I/O and OOP principles. Implemented inheritance and polymorphism for extensible architecture.",
      technologies: ["C++", "OOP", "File I/O", "Data Structures"],
      color: "from-violet-500 to-purple-400"
    },
    {
      icon: Cloud,
      title: "Weather Data Visualization",
      description: "Created Python tool fetching API data with interactive visualizations of weather patterns.",
      technologies: ["Python", "API Integration", "Data Visualization"],
      color: "from-orange-500 to-amber-400"
    }
  ];

  return (
    <section id="projects" className="py-24 px-6 relative overflow-hidden">
      {/* Background accents */}
      <div className="absolute right-0 top-1/4 w-96 h-96 bg-primary/5 rounded-full blur-3xl" />
      <div className="absolute left-0 bottom-1/4 w-72 h-72 bg-accent/5 rounded-full blur-3xl" />

      <div className="max-w-6xl mx-auto relative z-10">
        {/* Section header */}
        <div className="text-center mb-16">
          <span className="text-primary text-sm font-display uppercase tracking-widest mb-4 block">
            Portfolio
          </span>
          <h2 className="font-display text-4xl md:text-5xl font-bold mb-6">
            Featured{" "}
            <span className="gradient-text">Projects</span>
          </h2>
          <p className="text-muted-foreground max-w-xl mx-auto">
            Showcasing data analysis and software development projects that demonstrate technical skills and problem-solving abilities.
          </p>
        </div>

        {/* Projects grid */}
        <div className="grid md:grid-cols-2 lg:grid-cols-3 gap-6">
          {projects.map((project, index) => (
            <div
              key={project.title}
              className="group gradient-card rounded-2xl border border-border overflow-hidden hover:border-primary/30 transition-all duration-300 hover:-translate-y-2"
            >
              {/* Project image/icon area */}
              <div className={`h-48 bg-gradient-to-br ${project.color} opacity-80 flex items-center justify-center relative overflow-hidden`}>
                <project.icon className="w-16 h-16 text-white/90" />
                {/* Decorative pattern */}
                <div 
                  className="absolute inset-0 opacity-20"
                  style={{
                    backgroundImage: `radial-gradient(circle at 2px 2px, white 1px, transparent 0)`,
                    backgroundSize: '24px 24px'
                  }}
                />
              </div>

              {/* Content */}
              <div className="p-6">
                <h3 className="font-display text-xl font-bold mb-3 group-hover:text-primary transition-colors">
                  {project.title}
                </h3>
                <p className="text-muted-foreground text-sm leading-relaxed mb-4">
                  {project.description}
                </p>

                {/* Technologies */}
                <div className="flex flex-wrap gap-2">
                  {project.technologies.map((tech) => (
                    <span
                      key={tech}
                      className="px-3 py-1 rounded-full bg-secondary text-secondary-foreground text-xs"
                    >
                      {tech}
                    </span>
                  ))}
                </div>
              </div>
            </div>
          ))}
        </div>

        {/* CTA */}
        <div className="text-center mt-12">
          <Button
            variant="outline"
            size="lg"
            className="font-display border-primary/50 text-primary hover:bg-primary hover:text-primary-foreground transition-colors"
            onClick={() => document.getElementById('contact')?.scrollIntoView({ behavior: 'smooth' })}
          >
            <ExternalLink className="w-5 h-5 mr-2" />
            Interested in collaboration?
          </Button>
        </div>
      </div>
    </section>
  );
};

export default Projects;
