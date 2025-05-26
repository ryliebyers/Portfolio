using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using Pomelo.EntityFrameworkCore.MySql.Scaffolding.Internal;

namespace LMS.Models.LMSModels;

public partial class LMSContext : DbContext
{
    public LMSContext()
    {
    }

    public LMSContext(DbContextOptions<LMSContext> options)
        : base(options)
    {
    }

    public virtual DbSet<Administrator> Administrators { get; set; }

    public virtual DbSet<AspNetRole> AspNetRoles { get; set; }

    public virtual DbSet<AspNetRoleClaim> AspNetRoleClaims { get; set; }

    public virtual DbSet<AspNetUser> AspNetUsers { get; set; }

    public virtual DbSet<AspNetUserClaim> AspNetUserClaims { get; set; }

    public virtual DbSet<AspNetUserLogin> AspNetUserLogins { get; set; }

    public virtual DbSet<AspNetUserToken> AspNetUserTokens { get; set; }

    public virtual DbSet<Assignment> Assignments { get; set; }

    public virtual DbSet<AssignmentCategory> AssignmentCategories { get; set; }

    public virtual DbSet<Class> Classes { get; set; }

    public virtual DbSet<Course> Courses { get; set; }

    public virtual DbSet<Department> Departments { get; set; }

    public virtual DbSet<EfmigrationsHistory> EfmigrationsHistories { get; set; }

    public virtual DbSet<Enrolled> Enrolleds { get; set; }

    public virtual DbSet<Professor> Professors { get; set; }

    public virtual DbSet<Student> Students { get; set; }

    public virtual DbSet<Submission> Submissions { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        => optionsBuilder.UseMySql("name=LMS:LMSConnectionString", Microsoft.EntityFrameworkCore.ServerVersion.Parse("10.11.8-mariadb"));

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder
            .UseCollation("utf8mb4_general_ci")
            .HasCharSet("utf8mb4");

        modelBuilder.Entity<Administrator>(entity =>
        {
            entity.HasKey(e => e.UId).HasName("PRIMARY");

            entity
                .HasCharSet("latin1")
                .UseCollation("latin1_swedish_ci");

            entity.Property(e => e.UId)
                .HasMaxLength(8)
                .IsFixedLength()
                .HasColumnName("uID");
            entity.Property(e => e.Dob).HasColumnName("DOB");
            entity.Property(e => e.FName)
                .HasMaxLength(100)
                .HasColumnName("fName");
            entity.Property(e => e.LName)
                .HasMaxLength(100)
                .HasColumnName("lName");
        });

        modelBuilder.Entity<AspNetRole>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PRIMARY");

            entity.HasIndex(e => e.NormalizedName, "RoleNameIndex").IsUnique();

            entity.Property(e => e.Name).HasMaxLength(20);
            entity.Property(e => e.NormalizedName).HasMaxLength(256);
        });

        modelBuilder.Entity<AspNetRoleClaim>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PRIMARY");

            entity.HasIndex(e => e.RoleId, "IX_AspNetRoleClaims_RoleId");

            entity.Property(e => e.Id).HasColumnType("int(11)");

            entity.HasOne(d => d.Role).WithMany(p => p.AspNetRoleClaims).HasForeignKey(d => d.RoleId);
        });

        modelBuilder.Entity<AspNetUser>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PRIMARY");

            entity.HasIndex(e => e.NormalizedEmail, "EmailIndex");

            entity.HasIndex(e => e.NormalizedUserName, "UserNameIndex").IsUnique();

            entity.Property(e => e.AccessFailedCount).HasColumnType("int(11)");
            entity.Property(e => e.Email).HasMaxLength(256);
            entity.Property(e => e.LockoutEnd).HasMaxLength(6);
            entity.Property(e => e.NormalizedEmail).HasMaxLength(256);
            entity.Property(e => e.NormalizedUserName).HasMaxLength(256);
            entity.Property(e => e.UserName).HasMaxLength(20);

            entity.HasMany(d => d.Roles).WithMany(p => p.Users)
                .UsingEntity<Dictionary<string, object>>(
                    "AspNetUserRole",
                    r => r.HasOne<AspNetRole>().WithMany().HasForeignKey("RoleId"),
                    l => l.HasOne<AspNetUser>().WithMany().HasForeignKey("UserId"),
                    j =>
                    {
                        j.HasKey("UserId", "RoleId")
                            .HasName("PRIMARY")
                            .HasAnnotation("MySql:IndexPrefixLength", new[] { 0, 0 });
                        j.ToTable("AspNetUserRoles");
                        j.HasIndex(new[] { "RoleId" }, "IX_AspNetUserRoles_RoleId");
                    });
        });

        modelBuilder.Entity<AspNetUserClaim>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PRIMARY");

            entity.HasIndex(e => e.UserId, "IX_AspNetUserClaims_UserId");

            entity.Property(e => e.Id).HasColumnType("int(11)");

            entity.HasOne(d => d.User).WithMany(p => p.AspNetUserClaims).HasForeignKey(d => d.UserId);
        });

        modelBuilder.Entity<AspNetUserLogin>(entity =>
        {
            entity.HasKey(e => new { e.LoginProvider, e.ProviderKey })
                .HasName("PRIMARY")
                .HasAnnotation("MySql:IndexPrefixLength", new[] { 0, 0 });

            entity.HasIndex(e => e.UserId, "IX_AspNetUserLogins_UserId");

            entity.Property(e => e.LoginProvider).HasMaxLength(128);
            entity.Property(e => e.ProviderKey).HasMaxLength(128);

            entity.HasOne(d => d.User).WithMany(p => p.AspNetUserLogins).HasForeignKey(d => d.UserId);
        });

        modelBuilder.Entity<AspNetUserToken>(entity =>
        {
            entity.HasKey(e => new { e.UserId, e.LoginProvider, e.Name })
                .HasName("PRIMARY")
                .HasAnnotation("MySql:IndexPrefixLength", new[] { 0, 0, 0 });

            entity.Property(e => e.LoginProvider).HasMaxLength(128);
            entity.Property(e => e.Name).HasMaxLength(128);

            entity.HasOne(d => d.User).WithMany(p => p.AspNetUserTokens).HasForeignKey(d => d.UserId);
        });

        modelBuilder.Entity<Assignment>(entity =>
        {
            entity.HasKey(e => e.AssignmentId).HasName("PRIMARY");

            entity
                .HasCharSet("latin1")
                .UseCollation("latin1_swedish_ci");

            entity.HasIndex(e => e.Category, "Assignments_ibfk_1");

            entity.HasIndex(e => new { e.Name, e.Category }, "name_unique").IsUnique();

            entity.Property(e => e.AssignmentId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("AssignmentID");
            entity.Property(e => e.Category).HasColumnType("int(10) unsigned");
            entity.Property(e => e.Contents).HasMaxLength(8192);
            entity.Property(e => e.Due).HasColumnType("datetime");
            entity.Property(e => e.MaxPoints).HasColumnType("int(10) unsigned");
            entity.Property(e => e.Name).HasMaxLength(100);

            entity.HasOne(d => d.CategoryNavigation).WithMany(p => p.Assignments)
                .HasForeignKey(d => d.Category)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Assignments_ibfk_1");
        });

        modelBuilder.Entity<AssignmentCategory>(entity =>
        {
            entity.HasKey(e => e.CategoryId).HasName("PRIMARY");

            entity
                .HasCharSet("latin1")
                .UseCollation("latin1_swedish_ci");

            entity.HasIndex(e => e.InClass, "AssignmentCategories_ibfk_1");

            entity.HasIndex(e => new { e.Name, e.InClass }, "Name").IsUnique();

            entity.Property(e => e.CategoryId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("CategoryID");
            entity.Property(e => e.InClass).HasColumnType("int(10) unsigned");
            entity.Property(e => e.Name).HasMaxLength(100);
            entity.Property(e => e.Weight).HasColumnType("int(10) unsigned");

            entity.HasOne(d => d.InClassNavigation).WithMany(p => p.AssignmentCategories)
                .HasForeignKey(d => d.InClass)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("AssignmentCategories_ibfk_1");
        });

        modelBuilder.Entity<Class>(entity =>
        {
            entity.HasKey(e => e.ClassId).HasName("PRIMARY");

            entity
                .HasCharSet("latin1")
                .UseCollation("latin1_swedish_ci");

            entity.HasIndex(e => e.Listing, "Classes_ibfk_1");

            entity.HasIndex(e => new { e.Season, e.Year, e.Listing }, "Season").IsUnique();

            entity.HasIndex(e => e.TaughtBy, "Taught");

            entity.Property(e => e.ClassId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("ClassID");
            entity.Property(e => e.EndTime).HasColumnType("time");
            entity.Property(e => e.Listing).HasColumnType("int(10) unsigned");
            entity.Property(e => e.Location).HasMaxLength(100);
            entity.Property(e => e.Season).HasMaxLength(6);
            entity.Property(e => e.StartTime).HasColumnType("time");
            entity.Property(e => e.TaughtBy)
                .HasMaxLength(8)
                .IsFixedLength();
            entity.Property(e => e.Year).HasColumnType("int(10) unsigned");

            entity.HasOne(d => d.ListingNavigation).WithMany(p => p.Classes)
                .HasForeignKey(d => d.Listing)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Classes_ibfk_1");

            entity.HasOne(d => d.TaughtByNavigation).WithMany(p => p.Classes)
                .HasForeignKey(d => d.TaughtBy)
                .HasConstraintName("Taught");
        });

        modelBuilder.Entity<Course>(entity =>
        {
            entity.HasKey(e => e.CatalogId).HasName("PRIMARY");

            entity
                .HasCharSet("latin1")
                .UseCollation("latin1_swedish_ci");

            entity.HasIndex(e => e.Department, "Courses_ibfk_1");

            entity.HasIndex(e => new { e.Number, e.Department }, "Number").IsUnique();

            entity.Property(e => e.CatalogId)
                .HasColumnType("int(10) unsigned")
                .HasColumnName("CatalogID");
            entity.Property(e => e.Department).HasMaxLength(4);
            entity.Property(e => e.Name).HasMaxLength(100);
            entity.Property(e => e.Number).HasColumnType("int(10) unsigned");

            entity.HasOne(d => d.DepartmentNavigation).WithMany(p => p.Courses)
                .HasForeignKey(d => d.Department)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Courses_ibfk_1");
        });

        modelBuilder.Entity<Department>(entity =>
        {
            entity.HasKey(e => e.Subject).HasName("PRIMARY");

            entity
                .HasCharSet("latin1")
                .UseCollation("latin1_swedish_ci");

            entity.Property(e => e.Subject).HasMaxLength(4);
            entity.Property(e => e.Name).HasMaxLength(100);
        });

        modelBuilder.Entity<EfmigrationsHistory>(entity =>
        {
            entity.HasKey(e => e.MigrationId).HasName("PRIMARY");

            entity.ToTable("__EFMigrationsHistory");

            entity.Property(e => e.MigrationId).HasMaxLength(150);
            entity.Property(e => e.ProductVersion).HasMaxLength(32);
        });

        modelBuilder.Entity<Enrolled>(entity =>
        {
            entity.HasKey(e => new { e.Student, e.Class })
                .HasName("PRIMARY")
                .HasAnnotation("MySql:IndexPrefixLength", new[] { 0, 0 });

            entity
                .ToTable("Enrolled")
                .HasCharSet("latin1")
                .UseCollation("latin1_swedish_ci");

            entity.HasIndex(e => e.Class, "Enrolled_ibfk_2");

            entity.Property(e => e.Student)
                .HasMaxLength(8)
                .IsFixedLength();
            entity.Property(e => e.Class).HasColumnType("int(10) unsigned");
            entity.Property(e => e.Grade).HasMaxLength(2);

            entity.HasOne(d => d.ClassNavigation).WithMany(p => p.Enrolleds)
                .HasForeignKey(d => d.Class)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Enrolled_ibfk_2");

            entity.HasOne(d => d.StudentNavigation).WithMany(p => p.Enrolleds)
                .HasForeignKey(d => d.Student)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Enrolled_ibfk_1");
        });

        modelBuilder.Entity<Professor>(entity =>
        {
            entity.HasKey(e => e.UId).HasName("PRIMARY");

            entity
                .HasCharSet("latin1")
                .UseCollation("latin1_swedish_ci");

            entity.HasIndex(e => e.WorksIn, "Professors_ibfk_1");

            entity.Property(e => e.UId)
                .HasMaxLength(8)
                .IsFixedLength()
                .HasColumnName("uID");
            entity.Property(e => e.Dob).HasColumnName("DOB");
            entity.Property(e => e.FName)
                .HasMaxLength(100)
                .HasColumnName("fName");
            entity.Property(e => e.LName)
                .HasMaxLength(100)
                .HasColumnName("lName");
            entity.Property(e => e.WorksIn).HasMaxLength(4);

            entity.HasOne(d => d.WorksInNavigation).WithMany(p => p.Professors)
                .HasForeignKey(d => d.WorksIn)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Professors_ibfk_1");
        });

        modelBuilder.Entity<Student>(entity =>
        {
            entity.HasKey(e => e.UId).HasName("PRIMARY");

            entity
                .HasCharSet("latin1")
                .UseCollation("latin1_swedish_ci");

            entity.HasIndex(e => e.Major, "Students_ibfk_1");

            entity.Property(e => e.UId)
                .HasMaxLength(8)
                .IsFixedLength()
                .HasColumnName("uID");
            entity.Property(e => e.Dob).HasColumnName("DOB");
            entity.Property(e => e.FName)
                .HasMaxLength(100)
                .HasColumnName("fName");
            entity.Property(e => e.LName)
                .HasMaxLength(100)
                .HasColumnName("lName");
            entity.Property(e => e.Major).HasMaxLength(4);

            entity.HasOne(d => d.MajorNavigation).WithMany(p => p.Students)
                .HasForeignKey(d => d.Major)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Students_ibfk_1");
        });

        modelBuilder.Entity<Submission>(entity =>
        {
            entity.HasKey(e => new { e.Assignment, e.Student })
                .HasName("PRIMARY")
                .HasAnnotation("MySql:IndexPrefixLength", new[] { 0, 0 });

            entity
                .HasCharSet("latin1")
                .UseCollation("latin1_swedish_ci");

            entity.HasIndex(e => e.Student, "Submissions_ibfk_2");

            entity.Property(e => e.Assignment).HasColumnType("int(10) unsigned");
            entity.Property(e => e.Student)
                .HasMaxLength(8)
                .IsFixedLength();
            entity.Property(e => e.Score).HasColumnType("int(10) unsigned");
            entity.Property(e => e.SubmissionContents).HasMaxLength(8192);
            entity.Property(e => e.Time).HasColumnType("datetime");

            entity.HasOne(d => d.AssignmentNavigation).WithMany(p => p.Submissions)
                .HasForeignKey(d => d.Assignment)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Submissions_ibfk_1");

            entity.HasOne(d => d.StudentNavigation).WithMany(p => p.Submissions)
                .HasForeignKey(d => d.Student)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("Submissions_ibfk_2");
        });

        OnModelCreatingPartial(modelBuilder);
    }

    partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
}
