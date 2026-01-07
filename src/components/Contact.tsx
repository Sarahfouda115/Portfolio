import { Mail, Phone, Linkedin, MapPin, Send } from "lucide-react";
import { Button } from "./ui/button";

const Contact = () => {
  const contactInfo = [
    {
      icon: Mail,
      label: "Email",
      value: "sarahfouda2@gmail.com",
      href: "mailto:sarahfouda2@gmail.com"
    },
    {
      icon: Phone,
      label: "Phone",
      value: "+20 103 047 0965",
      href: "tel:+201030470965"
    },
    {
      icon: Linkedin,
      label: "LinkedIn",
      value: "linkedin.com/in/sarah-fouda",
      href: "https://linkedin.com/in/sarah-fouda-ab0405357"
    },
    {
      icon: MapPin,
      label: "Location",
      value: "Egypt",
      href: null
    }
  ];

  return (
    <section id="contact" className="py-24 px-6 relative overflow-hidden">
      {/* Background elements */}
      <div className="absolute inset-0 gradient-hero" />
      <div className="absolute left-1/2 top-1/2 -translate-x-1/2 -translate-y-1/2 w-[600px] h-[600px] bg-primary/5 rounded-full blur-3xl" />

      <div className="max-w-4xl mx-auto relative z-10">
        {/* Section header */}
        <div className="text-center mb-16">
          <span className="text-primary text-sm font-display uppercase tracking-widest mb-4 block">
            Get in Touch
          </span>
          <h2 className="font-display text-4xl md:text-5xl font-bold mb-6">
            Let's Work{" "}
            <span className="gradient-text">Together</span>
          </h2>
          <p className="text-muted-foreground max-w-xl mx-auto text-lg">
            Interested in collaboration or have an opportunity? I'd love to hear from you!
          </p>
        </div>

        {/* Contact cards */}
        <div className="grid sm:grid-cols-2 gap-4 mb-12">
          {contactInfo.map((item) => (
            <div
              key={item.label}
              className="gradient-card rounded-2xl border border-border p-6 hover:border-primary/30 transition-colors group"
            >
              {item.href ? (
                <a
                  href={item.href}
                  target={item.href.startsWith('http') ? '_blank' : undefined}
                  rel={item.href.startsWith('http') ? 'noopener noreferrer' : undefined}
                  className="flex items-center gap-4"
                >
                  <div className="w-12 h-12 rounded-xl bg-primary/10 flex items-center justify-center group-hover:bg-primary/20 transition-colors">
                    <item.icon className="w-6 h-6 text-primary" />
                  </div>
                  <div>
                    <span className="text-sm text-muted-foreground">{item.label}</span>
                    <p className="font-medium group-hover:text-primary transition-colors">{item.value}</p>
                  </div>
                </a>
              ) : (
                <div className="flex items-center gap-4">
                  <div className="w-12 h-12 rounded-xl bg-primary/10 flex items-center justify-center">
                    <item.icon className="w-6 h-6 text-primary" />
                  </div>
                  <div>
                    <span className="text-sm text-muted-foreground">{item.label}</span>
                    <p className="font-medium">{item.value}</p>
                  </div>
                </div>
              )}
            </div>
          ))}
        </div>

        {/* CTA Button */}
        <div className="text-center">
          <Button
            size="lg"
            className="gradient-primary text-primary-foreground font-display font-semibold px-10 py-6 text-lg glow-primary hover:scale-105 transition-transform"
            onClick={() => window.location.href = 'mailto:sarahfouda2@gmail.com'}
          >
            <Send className="w-5 h-5 mr-2" />
            Send me an Email
          </Button>
        </div>
      </div>
    </section>
  );
};

export default Contact;
