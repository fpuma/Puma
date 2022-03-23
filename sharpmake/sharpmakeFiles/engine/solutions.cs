namespace Puma
{
    [Sharpmake.Generate]
    class PumaEngineSolution : Puma.Common.IMySolution
    {
        public PumaEngineSolution()
            : base("Puma")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);
            conf.AddProject<Puma.PumaEngine>(target);
            conf.AddProject<Puma.EngineTest>(target);
            conf.AddProject<Puma.Asteroids>(target);
        }
    }

    [Sharpmake.Generate]
    class ExternLibs : Puma.Common.IMySolution
    {
        public ExternLibs()
            : base("ExternLibs")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddProject<Extern.Box2D>(target);
        }
    }
}

