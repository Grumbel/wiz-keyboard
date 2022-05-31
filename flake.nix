{
  description = "Simple toy keyboard/terminal application";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-22.05";
    flake-utils.url = "github:numtide/flake-utils";

    tinycmmc.url = "github:grumbel/tinycmmc";
    tinycmmc.inputs.nixpkgs.follows = "nixpkgs";
    tinycmmc.inputs.flake-utils.follows = "flake-utils";

    SDL_tty.url = "github:grumbel/SDL_tty";
    SDL_tty.inputs.nixpkgs.follows = "nixpkgs";
    SDL_tty.inputs.flake-utils.follows = "flake-utils";
    SDL_tty.inputs.tinycmmc.follows = "tinycmmc";
  };

  outputs = { self, nixpkgs, flake-utils, tinycmmc, SDL_tty }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
       in rec {
         packages = flake-utils.lib.flattenTree rec {
           wiz-keyboard = pkgs.stdenv.mkDerivation {
             name = "wiz-keyboard";
             src = nixpkgs.lib.cleanSource ./.;
             cmakeFlags = [];
             nativeBuildInputs = [
               pkgs.cmake
               pkgs.pkgconfig
               tinycmmc.defaultPackage.${system}
             ];
             buildInputs = [
               SDL_tty.defaultPackage.${system}

               pkgs.SDL
               pkgs.SDL_image
             ];
           };
        };
        defaultPackage = packages.wiz-keyboard;
      });
}
