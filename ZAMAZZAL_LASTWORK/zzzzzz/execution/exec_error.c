/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:51:41 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/27 18:39:04 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/exec.h"
# include <errno.h>

int    ft_perror(char *message)
{
    ft_putstr_fd(message, 2);
    ft_putstr_fd(": error is happen.", 2);
    if ((errno & E2BIG) == (E2BIG))
        ft_putstr_fd("Liste d'arguments trop longue.", 2);
    else if ((errno & EACCES) == (EACCES))
        ft_putstr_fd("Permission refusée.", 2);
    else if ((errno & EADDRINUSE) == (EADDRINUSE))
        ft_putstr_fd("Adresse déjà en cours d'utilisation.", 2);
    else if ((errno & EADDRNOTAVAIL) == (EADDRNOTAVAIL))
        ft_putstr_fd("Adresse non disponible.", 2);
    else if ((errno & EAFNOSUPPORT) == (EAFNOSUPPORT))
        ft_putstr_fd("Famille d'adresses non supportée.", 2);
    else if ((errno & EAGAIN) == (EAGAIN))
        ft_putstr_fd("Ressource temporairement indisponible.", 2);
    else if ((errno & EALREADY) == EALREADY)
        ft_putstr_fd("Connexion déjà en cours .", 2);
    else if ((errno & EBADF) == (EBADF))
        ft_putstr_fd("Mauvais descripteur de fichier.", 2);
    else if ((errno & EBADMSG) == (EBADMSG))
        ft_putstr_fd("Mauvais message.", 2);
    else if ((errno & EBUSY) == (EBUSY))
        ft_putstr_fd("Ressource ou périphérique occupé.", 2);
    else if ((errno & ECANCELED) == (ECANCELED))
        ft_putstr_fd("Opération annulée.", 2);
    else if ((errno & ECHILD) == (ECHILD))
        ft_putstr_fd("Pas de processus fils.", 2);
    else if ((errno & ECONNABORTED) == (ECONNABORTED))
        ft_putstr_fd("Connexion abandonnée.", 2);
    else if ((errno & ECHILD) == (ECHILD))
        ft_putstr_fd("Pas de processus fils.", 2);
    else if ((errno & ECONNREFUSED) == (ECONNREFUSED))
        ft_putstr_fd("Connexion refusée.", 2);
    else if ((errno & ECONNRESET) == (ECONNRESET))
        ft_putstr_fd("Connexion réinitialisée.", 2);
    else if ((errno & EDEADLK) == (EDEADLK))
        ft_putstr_fd("Blocage d'une ressource évité.", 2);
    else if ((errno & EDESTADDRREQ) == (EDESTADDRREQ))
        ft_putstr_fd("Adresse de destination nécessaire.", 2);
    else if ((errno & EDOM) == (EDOM))
        ft_putstr_fd("Argument mathématique hors du domaine de définition de la fonction.", 2);
    else if ((errno & EDQUOT) == (EDQUOT))
        ft_putstr_fd("Quota disque dépassé.", 2);
    else if ((errno & EEXIST) == (EEXIST))
        ft_putstr_fd("Fichier existant.", 2);
    else if ((errno & EFAULT) == (EFAULT))
        ft_putstr_fd("Mauvaise adresse.", 2);
    else if ((errno & EFBIG) == (EFBIG))
        ft_putstr_fd("Fichier trop grand.", 2);
    else if ((errno & EHOSTDOWN) == (EHOSTDOWN))
        ft_putstr_fd("Hôte éteint.", 2);
    else if ((errno & EHOSTUNREACH) == (EHOSTUNREACH))
        ft_putstr_fd("Hôte non accessible.", 2);
    else if ((errno & EIDRM) == (EIDRM))
        ft_putstr_fd("Identificateur supprimé.", 2);
    else if ((errno & EILSEQ) == (EILSEQ))
        ft_putstr_fd("Séquence d'octets illégale.", 2);
    else if ((errno & EINPROGRESS) == (EINPROGRESS))
        ft_putstr_fd("Opération en cours.", 2);
    else if ((errno & EINTR) == (EINTR))
        ft_putstr_fd("Appel système interrompu.", 2);
    else if ((errno & EINVAL) == (EINVAL))
        ft_putstr_fd("Argument invalide.", 2);
    else if ((errno & EIO) == (EIO))
        ft_putstr_fd("Erreur d'entrée-sortie.", 2);
    else if ((errno & EISCONN) == (EISCONN))
        ft_putstr_fd("La socket est connectée.", 2);
    else if ((errno & EISDIR) == (EISDIR))
        ft_putstr_fd("Est un répertoire.", 2);
    else if ((errno & ELOOP) == (ELOOP))
        ft_putstr_fd("Trop de niveaux de liens symboliques rencontrés.", 2);
    else if ((errno & EMFILE) == (EMFILE))
        ft_putstr_fd("Trop de fichiers ouverts.", 2);
    else if ((errno & EMLINK) == (EMLINK))
        ft_putstr_fd("Trop de liens symboliques.", 2);
    else if ((errno & EMSGSIZE) == (EMSGSIZE))
        ft_putstr_fd("Message trop long.", 2);
    else if ((errno & EMULTIHOP) == (EMULTIHOP))
        ft_putstr_fd("Tentative de saut multiple « Multihop ».", 2);
    else if ((errno & ENAMETOOLONG) == (ENAMETOOLONG))
        ft_putstr_fd("Nom de fichier trop long.", 2);
    else if ((errno & ENETDOWN) == (ENETDOWN))
        ft_putstr_fd("Le réseau est désactivé.", 2);
    else if ((errno & ENETRESET) == (ENETRESET))
        ft_putstr_fd("Connexion annulée par le réseau.", 2);
    else if ((errno & ENETUNREACH) == (ENETUNREACH))
        ft_putstr_fd("Réseau inaccessible.", 2);
    else if ((errno & ENFILE) == (ENFILE))
        ft_putstr_fd("Trop de fichiers ouverts sur le système.", 2);
    else if ((errno & ENOBUFS) == (ENOBUFS))
        ft_putstr_fd("Plus de tampons disponibles.", 2);
    else if ((errno & ENODATA) == (ENODATA))
        ft_putstr_fd("Pas de message disponible dans la file STREAM.", 2);
    else if ((errno & ENODEV) == (ENODEV))
        ft_putstr_fd("Périphérique inexistant.", 2);
    else if ((errno & ENOENT) == (ENOENT))
        ft_putstr_fd("Fichier ou répertoire inexistant.", 2);
    else if ((errno & ENOEXEC) == (ENOEXEC))
        ft_putstr_fd("Erreur de format d'exécution.", 2);   
    else if ((errno & ENOLCK) == (ENOLCK))
        ft_putstr_fd("Pas de verrou disponible .", 2);
    else if ((errno & ENOLINK) == (ENOLINK))
        ft_putstr_fd("Le lien a été coupé.", 2);
    else if ((errno & ENOMEM) == (ENOMEM))
        ft_putstr_fd("Pas assez de mémoire.", 2);
    else if ((errno & ENOMSG) == (ENOMSG))
        ft_putstr_fd("Pas de message du type attendu.", 2);
    else if ((errno & ENOPROTOOPT) == (ENOPROTOOPT))
        ft_putstr_fd("Protocole indisponible.", 2);
    else if ((errno & ENOSPC) == (ENOSPC))
        ft_putstr_fd("Plus de place sur le périphérique.", 2);
    else if ((errno & ENOSR) == (ENOSR))
        ft_putstr_fd("Pas de ressource STREAM.", 2);
    else if ((errno & ENOSTR) == (ENOSTR))
        ft_putstr_fd("Pas un STREAM.", 2);
    else if ((errno & ENOSYS) == (ENOSYS))
        ft_putstr_fd("Fonction non implémentée.", 2);
    else if ((errno & ENOTBLK) == (ENOTBLK))
        ft_putstr_fd("Périphérique de bloc requis.", 2);
    else if ((errno & ENOTCONN) == (ENOTCONN))
        ft_putstr_fd("La socket n'est pas connectée.", 2);
    else if ((errno & ENOTDIR) == (ENOTDIR))
        ft_putstr_fd("Pas un répertoire.", 2);
    else if ((errno & ENOTEMPTY) == (ENOTEMPTY))
        ft_putstr_fd("Répertoire non vide.", 2);
    else if ((errno & ENOTSOCK) == (ENOTSOCK))
        ft_putstr_fd("Pas une socket.", 2);
    else if ((errno & ENOTSUP) == (ENOTSUP))
        ft_putstr_fd("Opération non supportée.", 2);
    else if ((errno & ENOTTY) == (ENOTTY))
        ft_putstr_fd("Opération de contrôle d'entrée-sortie invalide.", 2);
    else if ((errno & ENXIO) == (ENXIO))
        ft_putstr_fd("Périphérique ou adresse inexistant.", 2);
    else if ((errno & EOPNOTSUPP) == (EOPNOTSUPP))
        ft_putstr_fd("Opération non supportée par la socket.", 2);
    else if ((errno & EOVERFLOW) == (EOVERFLOW))
        ft_putstr_fd("Valeur trop grande être stocké dans ce type de donnée.", 2);
    else if ((errno & EPERM) == (EPERM))
        ft_putstr_fd("Opération interdite.", 2);
    else if ((errno & EPFNOSUPPORT) == (EPFNOSUPPORT))
        ft_putstr_fd("Famille de protocole non supportée.", 2);
    else if ((errno & EPIPE) == (EPIPE))
        ft_putstr_fd("Tube brisé.", 2);
    else if ((errno & EPROTO) == (EPROTO))
        ft_putstr_fd("Erreur de protocole.", 2);
    else if ((errno & EPROTONOSUPPORT) == (EPROTONOSUPPORT))
        ft_putstr_fd("Protocole non supporté.", 2);
    else if ((errno & EPROTOTYPE) == (EPROTOTYPE))
        ft_putstr_fd("Mauvais type de protocole pour la socket.", 2);
    else if ((errno & ERANGE) == (ERANGE))
        ft_putstr_fd("Résultat trop grand.", 2);
    else if ((errno & EREMOTE) == (EREMOTE))
        ft_putstr_fd("L'objet est distant.", 2);
    else if ((errno & EROFS) == (EROFS))
        ft_putstr_fd("Système de fichiers en lecture seule.", 2);
    else if ((errno & ESHUTDOWN) == (ESHUTDOWN))
        ft_putstr_fd("Impossible d'envoyer après l'arrêt du point final du transport.", 2);
    else if ((errno & ESPIPE) == (ESPIPE))
        ft_putstr_fd("Recherche invalide.", 2);
    else if ((errno & ESOCKTNOSUPPORT) == (ESOCKTNOSUPPORT))
        ft_putstr_fd("Type de socket non supporté.", 2);
    else if ((errno & ESRCH) == (ESRCH))
        ft_putstr_fd("Processus inexistant.", 2);
    else if ((errno & ESTALE) == (ESTALE))
        ft_putstr_fd("Descripteur de fichier éventé, Cette erreur peut se produire pour NFS et d'autres systèmes de fichiers", 2);
    else if ((errno & ETIME) == (ETIME))
        ft_putstr_fd("Temporisation expirée.", 2);
    else if ((errno & ETIMEDOUT) == (ETIMEDOUT))
        ft_putstr_fd("Délai maximal de connexion écoulé.", 2);
    else if ((errno & ETXTBSY) == (ETXTBSY))
        ft_putstr_fd("Fichier texte occupé.", 2);
    else if ((errno & EUSERS) == (EUSERS))
        ft_putstr_fd("Trop d'utilisateurs.", 2);
    else if ((errno & EWOULDBLOCK) == (EWOULDBLOCK))
        ft_putstr_fd("L'opération serait bloquante.", 2);
    else if ((errno & EXDEV) == (EXDEV))
        ft_putstr_fd("Lien inapproprié.", 2);
    else
        ft_putstr_fd("indefiend error.",  2);
    ft_putchar('\n');
    return (-1);
}