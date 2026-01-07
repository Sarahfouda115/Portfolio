import { Briefcase, Calendar, ArrowRight } from "lucide-react";

const Experience = () => {
  const experience = {
    role: "Data Analysis Intern",
    company: "Digital Egypt Pioneers Initiative (DEPI) | NEXT Company",
    period: "2023 - Present",
    responsibilities: [
      "Implemented data analysis pipeline: collection, cleaning, analysis, and visualization",
      "Developed interactive dashboards using Power BI to translate complex datasets into business insights",
      "Collaborated in team projects using Python (Pandas, NumPy) and SQL for data processing"
    ],
    technologies: ["Python", "Pandas", "NumPy", "Power BI", "SQL"]
  };

  return (
    <section id="experience" className="py-24 px-6 bg-muted/30 relative">
      {/* Background accent */}
      <div className="absolute left-0 top-1/2 -translate-y-1/2 w-72 h-72 bg-primary/5 rounded-full blur-3xl" />
      
      <div className="max-w-4xl mx-auto relative z-10">
        {/* Section header */}
        <div className="text-center mb-16">
          <span className="text-primary text-sm font-display uppercase tracking-widest mb-4 block">
            Experience
          </span>
          <h2 className="font-display text-4xl md:text-5xl font-bold">
            Professional{" "}
            <span className="gradient-text">Journey</span>
          </h2>
        </div>

        {/* Experience card */}
        <div className="gradient-card rounded-3xl border border-border p-8 md:p-10 hover:border-primary/30 transition-colors">
          <div className="flex flex-col gap-6">
            {/* Header */}
            <div className="flex flex-col md:flex-row md:items-start gap-4">
              <div className="w-14 h-14 rounded-2xl gradient-primary flex items-center justify-center shrink-0">
                <Briefcase className="w-7 h-7 text-primary-foreground" />
              </div>
              <div className="flex-1">
                <h3 className="font-display text-2xl font-bold mb-1">{experience.role}</h3>
                <p className="text-muted-foreground">{experience.company}</p>
                <div className="flex items-center gap-2 mt-2 text-primary text-sm">
                  <Calendar className="w-4 h-4" />
                  <span>{experience.period}</span>
                </div>
              </div>
            </div>

            {/* Responsibilities */}
            <div className="space-y-3 mt-4">
              {experience.responsibilities.map((item, index) => (
                <div key={index} className="flex gap-3 items-start">
                  <ArrowRight className="w-5 h-5 text-primary shrink-0 mt-0.5" />
                  <p className="text-muted-foreground leading-relaxed">{item}</p>
                </div>
              ))}
            </div>

            {/* Technologies */}
            <div className="flex flex-wrap gap-2 mt-4 pt-6 border-t border-border">
              {experience.technologies.map((tech) => (
                <span
                  key={tech}
                  className="px-4 py-1.5 rounded-full bg-primary/10 text-primary text-sm font-medium"
                >
                  {tech}
                </span>
              ))}
            </div>
          </div>
        </div>

        {/* Certification badge */}
        <div className="mt-8 flex items-center justify-center">
          <div className="inline-flex items-center gap-3 px-6 py-3 rounded-full glass">
            <div className="w-3 h-3 rounded-full bg-primary animate-pulse" />
            <span className="text-muted-foreground text-sm">
              <span className="text-foreground font-medium">DEPI Data Analysis Certification</span> — In Progress
            </span>
          </div>
        </div>
      </div>
    </section>
  );
};

export default Experience;
