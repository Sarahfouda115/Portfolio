import { Mail, Linkedin, Phone, ChevronDown } from "lucide-react";
import { Button } from "./ui/button";

const Hero = () => {
  return (
    <section className="min-h-screen gradient-hero relative flex flex-col items-center justify-center px-6 overflow-hidden">
      {/* Background decoration */}
      <div className="absolute inset-0 overflow-hidden pointer-events-none">
        <div className="absolute top-1/4 -left-32 w-96 h-96 bg-primary/5 rounded-full blur-3xl animate-float" />
        <div className="absolute bottom-1/4 -right-32 w-96 h-96 bg-accent/5 rounded-full blur-3xl animate-float" style={{ animationDelay: '3s' }} />
        <div className="absolute top-1/2 left-1/2 -translate-x-1/2 -translate-y-1/2 w-[800px] h-[800px] bg-primary/3 rounded-full blur-[120px]" />
      </div>

      {/* Grid pattern overlay */}
      <div 
        className="absolute inset-0 opacity-[0.03]"
        style={{
          backgroundImage: `
            linear-gradient(hsl(175 80% 50%) 1px, transparent 1px),
            linear-gradient(90deg, hsl(175 80% 50%) 1px, transparent 1px)
          `,
          backgroundSize: '60px 60px'
        }}
      />

      <div className="relative z-10 max-w-4xl mx-auto text-center">
        {/* Status badge */}
        <div className="inline-flex items-center gap-2 px-4 py-2 rounded-full glass mb-8 animate-fade-up opacity-0" style={{ animationDelay: '0.1s' }}>
          <span className="w-2 h-2 rounded-full bg-primary animate-pulse" />
          <span className="text-sm text-muted-foreground">Open to opportunities</span>
        </div>

        {/* Name */}
        <h1 className="font-display text-5xl md:text-7xl lg:text-8xl font-bold mb-6 animate-fade-up opacity-0" style={{ animationDelay: '0.2s' }}>
          Sara Hemaia{" "}
          <span className="gradient-text">Fouda</span>
        </h1>

        {/* Title */}
        <p className="text-xl md:text-2xl text-muted-foreground mb-4 animate-fade-up opacity-0 font-display" style={{ animationDelay: '0.3s' }}>
          AI Student & Data Analyst
        </p>

        {/* Description */}
        <p className="text-lg text-muted-foreground/80 max-w-2xl mx-auto mb-10 leading-relaxed animate-fade-up opacity-0" style={{ animationDelay: '0.4s' }}>
          Pursuing a Bachelor's in Artificial Intelligence with a focus on data analysis 
          and machine learning. Building intelligent solutions with Python, Power BI, and modern analytics tools.
        </p>

        {/* CTA Buttons */}
        <div className="flex flex-col sm:flex-row gap-4 justify-center items-center animate-fade-up opacity-0" style={{ animationDelay: '0.5s' }}>
          <Button
            size="lg"
            className="gradient-primary text-primary-foreground font-display font-semibold px-8 glow-primary hover:scale-105 transition-transform"
            onClick={() => document.getElementById('contact')?.scrollIntoView({ behavior: 'smooth' })}
          >
            <Mail className="w-5 h-5 mr-2" />
            Get in Touch
          </Button>
          <Button
            size="lg"
            variant="outline"
            className="border-border hover:border-primary hover:text-primary transition-colors font-display"
            onClick={() => document.getElementById('projects')?.scrollIntoView({ behavior: 'smooth' })}
          >
            View Projects
          </Button>
        </div>

        {/* Social links */}
        <div className="flex gap-4 justify-center mt-12 animate-fade-up opacity-0" style={{ animationDelay: '0.6s' }}>
          <a
            href="tel:+201030470965"
            className="p-3 rounded-full border border-border hover:border-primary hover:text-primary transition-colors"
            aria-label="Phone"
          >
            <Phone className="w-5 h-5" />
          </a>
          <a
            href="mailto:sarahfouda2@gmail.com"
            className="p-3 rounded-full border border-border hover:border-primary hover:text-primary transition-colors"
            aria-label="Email"
          >
            <Mail className="w-5 h-5" />
          </a>
          <a
            href="https://linkedin.com/in/sarah-fouda-ab0405357"
            target="_blank"
            rel="noopener noreferrer"
            className="p-3 rounded-full border border-border hover:border-primary hover:text-primary transition-colors"
            aria-label="LinkedIn"
          >
            <Linkedin className="w-5 h-5" />
          </a>
        </div>
      </div>

      {/* Scroll indicator */}
      <div className="absolute bottom-8 left-1/2 -translate-x-1/2 animate-fade-up opacity-0" style={{ animationDelay: '0.8s' }}>
        <button
          onClick={() => document.getElementById('about')?.scrollIntoView({ behavior: 'smooth' })}
          className="flex flex-col items-center gap-2 text-muted-foreground hover:text-primary transition-colors"
        >
          <span className="text-xs uppercase tracking-widest">Scroll</span>
          <ChevronDown className="w-5 h-5 animate-bounce" />
        </button>
      </div>
    </section>
  );
};

export default Hero;
