{
  description = "Simple toy keyboard/terminal application";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";
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
       in {
         packages = rec {
           default = wiz-keyboard;

           wiz-keyboard = pkgs.stdenv.mkDerivation {
             pname = "wiz-keyboard";
             version = "0.0.0";

             src = nixpkgs.lib.cleanSource ./.;

             nativeBuildInputs = with pkgs; [
               cmake
               pkg-config
             ] ++ [
               tinycmmc.packages.${system}.default
             ];

             buildInputs = with pkgs; [
               SDL
               SDL_image
             ] ++ [
               SDL_tty.packages.${system}.default
             ];
           };
        };
       }
    );
}
