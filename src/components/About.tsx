import { GraduationCap, Brain, Code2, BarChart3 } from "lucide-react";

const About = () => {
  const highlights = [
    {
      icon: Brain,
      title: "AI Focus",
      description: "Specializing in Artificial Intelligence with strong mathematical foundations"
    },
    {
      icon: BarChart3,
      title: "Data Analysis",
      description: "Experienced in building data pipelines and interactive dashboards"
    },
    {
      icon: Code2,
      title: "Development",
      description: "Proficient in Python, C++, and modern data tools"
    },
    {
      icon: GraduationCap,
      title: "Academic Excellence",
      description: "Maintaining a 3.8/4.0 GPA with distinction"
    }
  ];

  return (
    <section id="about" className="py-24 px-6 relative">
      <div className="max-w-6xl mx-auto">
        {/* Section header */}
        <div className="text-center mb-16">
          <span className="text-primary text-sm font-display uppercase tracking-widest mb-4 block">
            About Me
          </span>
          <h2 className="font-display text-4xl md:text-5xl font-bold mb-6">
            Passionate about{" "}
            <span className="gradient-text">AI & Data</span>
          </h2>
          <p className="text-muted-foreground max-w-2xl mx-auto text-lg leading-relaxed">
            Detail-oriented individual with a strong academic background in Artificial Intelligence 
            and a solid foundation in mathematics and analytical thinking. Excellent communicator 
            with demonstrated teamwork abilities and a fast learning capacity.
          </p>
        </div>

        {/* Highlights grid */}
        <div className="grid md:grid-cols-2 lg:grid-cols-4 gap-6">
          {highlights.map((item, index) => (
            <div
              key={item.title}
              className="group gradient-card p-6 rounded-2xl border border-border hover:border-primary/50 transition-all duration-300 hover:-translate-y-1"
              style={{ animationDelay: `${index * 0.1}s` }}
            >
              <div className="w-12 h-12 rounded-xl gradient-primary flex items-center justify-center mb-4 group-hover:glow-primary transition-shadow">
                <item.icon className="w-6 h-6 text-primary-foreground" />
              </div>
              <h3 className="font-display font-semibold text-lg mb-2">{item.title}</h3>
              <p className="text-muted-foreground text-sm leading-relaxed">{item.description}</p>
            </div>
          ))}
        </div>

        {/* Education card */}
        <div className="mt-16 gradient-card rounded-2xl border border-border p-8 md:p-10">
          <div className="flex flex-col md:flex-row gap-8 items-start">
            <div className="w-16 h-16 rounded-2xl gradient-primary flex items-center justify-center shrink-0">
              <GraduationCap className="w-8 h-8 text-primary-foreground" />
            </div>
            <div className="flex-1">
              <span className="text-primary text-sm font-display uppercase tracking-wider">Education</span>
              <h3 className="font-display text-2xl font-bold mt-2 mb-1">Bachelor of Artificial Intelligence</h3>
              <p className="text-muted-foreground mb-4">Zagazig National University (ZNU), Egypt • 2023 - 2027</p>
              <div className="flex flex-wrap gap-3">
                <span className="px-4 py-1.5 rounded-full bg-primary/10 text-primary text-sm font-medium">
                  GPA: 3.8/4.0
                </span>
                <span className="px-4 py-1.5 rounded-full bg-secondary text-secondary-foreground text-sm">
                  Algorithms
                </span>
                <span className="px-4 py-1.5 rounded-full bg-secondary text-secondary-foreground text-sm">
                  Data Structures
                </span>
                <span className="px-4 py-1.5 rounded-full bg-secondary text-secondary-foreground text-sm">
                  Mathematical Foundations of AI
                </span>
              </div>
            </div>
          </div>
        </div>
      </div>
    </section>
  );
};

export default About;
